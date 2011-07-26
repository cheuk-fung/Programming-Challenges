" This must be first, because it changes other options as a side effect.
set nocompatible

" allow backspacing over everything in insert mode
set backspace=indent,eol,start

syntax on

set backup		" keep a backup file
set ruler		" show the cursor position all the time
set showcmd		" display incomplete commands
set incsearch		" do incremental searching
set shiftwidth=4
set expandtab
set number
set completeopt=longest,menu
set autochdir
set ignorecase smartcase
set hlsearch
set hidden

colorscheme evening

" Only do this part when compiled with support for autocommands.
if has("autocmd")
  filetype plugin indent on
else
  set autoindent		" always set autoindenting on
endif " has("autocmd")
