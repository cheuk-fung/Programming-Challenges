" Use Vim settings, rather then Vi settings (much better!).
" This must be first, because it changes other options as a side effect.
set nocompatible

" allow backspacing over everything in insert mode
set backspace=indent,eol,start

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
set hidden
set hlsearch
set autoindent		" always set autoindenting on

syntax on
filetype plugin indent on

inoremap {<CR>    {<CR>}<Esc>O
vnoremap {<CR>   S{<CR>}<Esc>Pk=iB

" In many terminal emulators the mouse works just fine, thus enable it.
if has('mouse')
    set mouse=a
endif
