#ifndef CKAGFX_H
#define CKAGFX_H

extern ID3D11Device* global_device;
extern ID3D11DeviceContext* global_context;

struct GFXManager
{
	float background_color[4];

	UINT create_device_flags;

	DXPtr<ID3D11Device> device;
	DXPtr<ID3D11DeviceContext> context;

	DXPtr<IDXGISwapChain> swap_chain;

	DXPtr<ID3D11RenderTargetView> render_target_view;
	DXPtr<ID3D11DepthStencilView> depth_stencil_view;

	DXPtr<ID3D11RasterizerState> raster_state;
	DXPtr<ID3D11BlendState> blend_state;

	static GFXManager* inst;
	static GFXManager* Inst();

	void ReportLiveDXObjects();

	static void BegDraw();
	void PrivBegDraw();
	static void EndDraw();
	void PrivEndDraw();
	static void Init( HWND window, int width, int height );
	void PrivInit( HWND window, int width, int height );
	static void Term();

	GFXManager() = default;
	~GFXManager();
	GFXManager(const GFXManager&) = delete;
	GFXManager& operator=(const GFXManager&) = delete;
};

#endif // CKAGFX
