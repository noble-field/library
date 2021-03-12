" Settings
let library_path = "~/kyopro/library"

syntax on

" Tab Setting
set tabstop=4
set shiftwidth=4
set autoindent
set smartindent

" Change Vim's Tab
nnoremap <C-t> :tabe<Space>
nnoremap t gt
nnoremap T gT
inoremap <C-t> <Esc>gta
inoremap <C-S-t> <Esc>gTa

" Change Mode
nnoremap <C-]> a
inoremap <C-]> <Esc>
vnoremap <C-]> <Esc>

" Move Cursor
set mouse=a
nnoremap <C-S-Left> <Home>
nnoremap <C-S-Right> <End>
inoremap <C-S-Left> <Home>
inoremap <C-S-Right> <End>

" Undo & Redo
nnoremap r <C-r>

" Move Line(s)
nnoremap <C-S-Up> "zdd<Up>"zP
nnoremap <C-S-Down> "zdd"zp
inoremap <C-S-Down> <Esc>"zdd"zpA
inoremap <C-S-Up> <Esc>"zdd<Up>"zPA
vnoremap <C-S-Up> "zx<Up>"zP`[V`]
vnoremap <C-S-Down> "zx"zp`[V`]

" Cut & Paste
vnoremap <BS> "_d
vnoremap <C-x> d
vnoremap <C-S-c> y
inoremap <C-v> <Esc>pa
inoremap <C-BS> <Esc>dba

" Indent Line(s)
nnoremap <Tab> >>
nnoremap <S-Tab> <<
inoremap <S-Tab> <Esc><<i
vnoremap <Tab> >`[V`]
vnoremap <S-Tab> <`[V`]

" Serach & Replace
nnoremap <silent> <Space><Space> :let @/ = '\<'.expand('<cword>').'\>'<CR>:set hlsearch<CR>
nnoremap <silent> <Esc><Esc> :set nohlsearch<CR>
nmap # <Space><Space>:%s/<C-r>///g<Left><Left>

" Comment Out
autocmd FIleType c setlocal commentstring=\/\/\ %s
autocmd FIleType cpp setlocal commentstring=\/\/\ %s
autocmd FileType python setlocal commentstring=#\ %s
autocmd FileType ruby setlocal commentstring=$\ %s
autocmd FileType *.sh setlocal commentstring=#\ %s
nmap <C-_> gcc
imap <C-_> <Esc>gcca
vmap <C-_> gc

" Library paste
let mapleader = library_path
nnoremap <C-L> :r<Space><Leader>/
inoremap <C-L> <Esc>:r<Space><Leader>/
