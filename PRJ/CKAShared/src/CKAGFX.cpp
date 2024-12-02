#include "Common.h"

/* Included by Common.h */

ID3D11Device* global_device = nullptr;
ID3D11DeviceContext* global_context = nullptr;

GFXManager* GFXManager::inst = nullptr;

GFXManager* GFXManager::Inst()
{
	if ( inst == nullptr )
	{
		inst = new GFXManager();
	}
	return inst;
}

void GFXManager::ReportLiveDXObjects()
{
#ifdef _DEBUG
	DXPtr<ID3D11Debug> debug_dev;
	Verify( Inst()->device->QueryInterface( IID_PPV_ARGS( &debug_dev ) ) );

	debug_dev->ReportLiveDeviceObjects( D3D11_RLDO_IGNORE_INTERNAL );
#endif
}

void GFXManager::BegDraw()
{
	Inst()->PrivBegDraw();
}
void GFXManager::PrivBegDraw()
{
	context->ClearRenderTargetView( render_target_view, background_color );
	context->ClearDepthStencilView( depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void GFXManager::EndDraw()
{
	Inst()->PrivEndDraw();
}
void GFXManager::PrivEndDraw()
{
	swap_chain->Present( 0, 0 );
}

void GFXManager::Init( HWND window, int width, int height )
{
	Inst()->PrivInit( window, width, height );
}
void GFXManager::PrivInit( HWND window, int width, int height )
{
	//background_color[0] = 0.1f;
	//background_color[1] = 0.2f;
	//background_color[2] = 0.3f;
	background_color[0] = 0.0f;
	background_color[1] = 0.0f;
	background_color[2] = 0.0f;
	background_color[3] = 1.0f;

	create_device_flags = 0;
#ifdef _DEBUG
	create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	Verify( D3D11CreateDevice
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		create_device_flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&device,
		nullptr,
		&context
	) );

	global_device = device;
	global_context = context;

	DXPtr<IDXGIDevice> dxgi_device = nullptr;
	Verify( device->QueryInterface( IID_PPV_ARGS( &dxgi_device ) ) );

	DXPtr<IDXGIAdapter> adapter = nullptr;
	Verify( dxgi_device->GetAdapter( &adapter ) );

	DXPtr<IDXGIFactory> dxgi_factory1 = nullptr;
	Verify( adapter->GetParent( IID_PPV_ARGS( &dxgi_factory1 ) ) );

	DXGI_SAMPLE_DESC sample_desc = {};
	sample_desc.Count = 4;
	sample_desc.Quality = static_cast<UINT>( D3D11_STANDARD_MULTISAMPLE_PATTERN );

	{ // Create swap chain
		DXGI_MODE_DESC buffer_desc = {};
		buffer_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferCount = 2;
		swap_chain_desc.BufferDesc = buffer_desc;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.OutputWindow = window;
		swap_chain_desc.SampleDesc = sample_desc;
		swap_chain_desc.Windowed = true;

		Verify( dxgi_factory1->CreateSwapChain( device, &swap_chain_desc, &swap_chain ) );
	}

	{ // Create back buffer
		DXPtr<ID3D11Texture2D> back_buffer = nullptr;
		Verify( swap_chain->GetBuffer( 0, IID_PPV_ARGS( &back_buffer ) ) );

		Verify( device->CreateRenderTargetView( back_buffer, nullptr, &render_target_view ) );
	}

	{ // Create rasterizer state
		D3D11_RASTERIZER_DESC raster_desc = {};
		raster_desc.FillMode = D3D11_FILL_SOLID;
		raster_desc.CullMode = D3D11_CULL_BACK;
		raster_desc.FrontCounterClockwise = true;
		raster_desc.DepthBias = 0;
		raster_desc.SlopeScaledDepthBias = 0.0f;
		raster_desc.DepthBiasClamp = 0.0f;
		raster_desc.DepthClipEnable = true;
		raster_desc.ScissorEnable = false;
		raster_desc.MultisampleEnable = true;
		raster_desc.AntialiasedLineEnable = true;

		Verify( device->CreateRasterizerState( &raster_desc, &raster_state ) );
		context->RSSetState( raster_state );
	}

	{ // Create depth stencil
		D3D11_TEXTURE2D_DESC depth_desc = {};
		depth_desc.Width = (UINT)width;
		depth_desc.Height = (UINT)height;
		depth_desc.MipLevels = 1;
		depth_desc.ArraySize = 1;
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.SampleDesc = sample_desc;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.CPUAccessFlags = 0;
		depth_desc.MiscFlags = 0;

		DXPtr<ID3D11Texture2D> depth_stencil;
		Verify( device->CreateTexture2D( &depth_desc, nullptr, &depth_stencil ) );

		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
		dsv_desc.Format = depth_desc.Format;
		dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		dsv_desc.Texture2D.MipSlice = 0;

		Verify( device->CreateDepthStencilView( depth_stencil, &dsv_desc, &depth_stencil_view ) );
	}

	context->OMSetRenderTargets( 1, &render_target_view, depth_stencil_view );

	{ // Create blend state
		D3D11_BLEND_DESC blend_desc;
		blend_desc.AlphaToCoverageEnable = false;
		blend_desc.IndependentBlendEnable = false;
		blend_desc.RenderTarget[0].BlendEnable = true;
		blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Verify( device->CreateBlendState( &blend_desc, &blend_state ) );

		context->OMSetBlendState( blend_state, nullptr, 0xffffffff );
	}

	{ // Set viewport
		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		context->RSSetViewports( 1, &viewport );
	}
}
void GFXManager::Term()
{
	delete inst;
	inst = nullptr;
}

GFXManager::~GFXManager()
{
}
