;; Display/Interface

(global-linum-mode 1)
(setq linum-format "%d ")
(setq column-number-mode t)
(setq-default show-trailing-whitespace t)
(show-paren-mode 1)
(setq visible-bell nil)
(setq ring-bell-function 'ignore)
(add-to-list 'default-frame-alist '(fullscreen . maximized))
(set-default-font "Fira Code-12")
(setq inhibit-splash-screen t)
(split-window-horizontally)


(when (window-system)
  (menu-bar-mode -1)
  (toggle-scroll-bar -1)
  (tool-bar-mode -1)
  (fringe-mode 0)
  (blink-cursor-mode -1)
  (set-default-font "Fira Code"))


(electric-pair-mode 1)
(delete-selection-mode t)
(transient-mark-mode t)
(setq x-select-enable-clipboard t)
(setq-default indicate-empty-lines t)
(toggle-indicate-empty-lines 1)


(setq undo-limit 20000000)
(setq undo-strong-limit 40000000)
(setq make-backup-files nil)
(setq auto-save-default nil)

(global-set-key (kbd "RET") 'newline-and-indent)
(defalias 'yes-or-no-p 'y-or-n-p)

;; C++ Stuff
(setq initial-major-mode 'c-mode)
(require 'cc-mode)
(defun chris-c-mode-common-hook ()
  (setq tab-width 4
	indent-tabs-mode nil
	c-default-style "bsd"
	c-basic-offset 4
	c-indent-level 4)
; (setq-default c-basic-offset 4)
)
(add-hook 'c-mode-common-hook 'chris-c-mode-common-hook)
(c-set-offset 'case-label '+)



;; Bland Colors
(setq bg-color "#36393E")
(setq fg-color "#A7A6A5")
(setq blue-gray "#89ABE3")
(setq comment-color "#DDA2CA")
(setq hl-color "#212429")
(setq region-color "#704A80")

;; Mode Line Colors
(setq mode-line-bg-color blue-gray)
(setq mode-line-fg-color "#202340")

; Bright Colors
(setq blue-green "#5BCBC4")
(setq gold "#FFC400")
(setq purple "#C792EA")
(setq red "#FF516D")
(setq light-green "#C2E982")
(setq blue "#74B1FF")
(setq red-orange "#F77669")

;; Dark Colors
(setq dark-purple "#31243A")

;; Various Colors
(setq black "#000000")
(setq white "#FFFFFF")
(setq background-gray "#263238")
(setq gray "#546D7A")
(setq foreground-gray "#CDD3BC")

(setq alert-color light-green)

(set-background-color bg-color)
(set-foreground-color fg-color)

(set-face-foreground 'mode-line mode-line-fg-color)
(set-face-background 'mode-line mode-line-bg-color)
(set-face-foreground 'mode-line-inactive mode-line-bg-color)
(set-face-background 'mode-line-inactive mode-line-fg-color)
(set-face-foreground 'mode-line-emphasis mode-line-fg-color)
(set-face-foreground 'mode-line-highlight mode-line-fg-color)
(set-face-foreground 'mode-line-buffer-id mode-line-fg-color)
;(set-face-foreground 'mode-line-emphasis comment-color)
;(set-face-foreground 'mode-line-highlight comment-color)
;(set-face-foreground 'mode-line-buffer-id comment-color)

(set-face-attribute 'font-lock-builtin-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-comment-face nil :foreground comment-color)
(set-face-attribute 'font-lock-constant-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-doc-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-function-name-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-keyword-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-string-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-type-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-variable-name-face nil :foreground fg-color)

(set-face-attribute 'default nil :foreground fg-color)
(set-face-attribute 'font-lock-builtin-face nil :foreground blue-gray)
(set-face-attribute 'font-lock-comment-delimiter-face nil :foreground comment-color)
(set-face-attribute 'font-lock-comment-face nil :foreground comment-color)
(set-face-attribute 'font-lock-negation-char-face nil :foreground purple)
(set-face-attribute 'font-lock-preprocessor-face nil :foreground purple)
(set-face-attribute 'font-lock-regexp-grouping-backslash nil :foreground purple)
(set-face-attribute 'font-lock-regexp-grouping-construct nil :foreground purple)
(set-face-attribute 'font-lock-warning-face nil :foreground purple)
(set-face-attribute 'shadow nil :foreground blue-green)
(set-face-attribute 'success nil :foreground light-green)
(set-face-attribute 'error nil :foreground red)
(set-face-attribute 'warning nil :foreground red-orange);

(set-face-foreground 'linum purple)
(set-face-background 'fringe bg-color)
(set-face-background 'trailing-whitespace purple)

(set-face-foreground 'minibuffer-prompt blue-gray)
(set-face-background 'cursor gray)

(global-hl-line-mode 1)
(set-face-background 'hl-line hl-color)
(set-face-background 'region region-color)
(set-face-background 'region dark-purple)


(setq fixme-modes '(c++-mode c-mode emacs-lisp-mode))
(make-face 'font-lock-fixme-face)
(make-face 'font-lock-todo-face)
(make-face 'font-lock-bug-face)
(make-face 'font-lock-note-face)
(mapc (lambda (mode)
	(font-lock-add-keywords
	 mode
	 '(("\\<\\(FIXME\\)" 1 'font-lock-fixme-face t)
	   ("\\<\\(TODO\\)" 1 'font-lock-todo-face t)
	   ("\\<\\(BUG\\)" 1 'font-lock-bug-face t)
	   ("\\<\\(NOTE\\)" 1 'font-lock-note-face t))))
      fixme-modes)
(modify-face 'font-lock-fixme-face alert-color nil nil t nil nil nil nil)
(modify-face 'font-lock-todo-face alert-color nil nil t nil nil nil nil)
(modify-face 'font-lock-bug-face alert-color nil nil t nil nil nil nil)
(modify-face 'font-lock-note-face alert-color nil nil t nil nil nil nil)





;; Package initialization
(require 'package)
(package-initialize)
(setq package-archives '(("gnu" . "https://elpa.gnu.org/packages/")
			 ("melpa" . "https://melpa.org/packages/")))

(require 'ido-completing-read+)
(ido-mode 1)
(ido-everywhere 1)
(ido-ubiquitous-mode 1)
(require 'ido-vertical-mode)
(ido-vertical-mode 1)
(setq ido-vertical-mode-define-keys 'C-n-and-C-p-only)
(set-face-foreground 'ido-subdir purple)
(set-face-foreground 'ido-first-match blue-gray)
(set-face-foreground 'ido-only-match blue-gray)

(require 'evil)
(evil-mode t)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages (quote (evil ido-completing-read+))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
