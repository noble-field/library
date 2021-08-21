syntax on

" beep-off
set belloff=all

" vim-airline
let g:airline_theme = 'wombat'
let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts = 1

" Line Number
set number
hi LineNr ctermbg=0 ctermfg=172
hi CursorLineNr ctermbg=8 ctermfg=172
set cursorline
hi clear CursorLine

" Tab Setting
set tabstop=4
set shiftwidth=4
set autoindent
set smartindent

" Change Vim's Tab
nnoremap <C-t> :tabe 
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
nmap <C-\> gcc
imap <C-\> <Esc>gcca
vmap <C-\> gc

" Select All
nnoremap <C-A> ggVG

" Save
nnoremap ss :w<CR>
inoremap <C-W> <Esc>:w<CR>

" fzf
set rtp+=~/.fzf
nnoremap <C-P> :Files<CR>
inoremap <C-P> <Esc>:Files<CR>

function! LibraryPaste()
	call fzf#run({
		\ 'sink': 'read',
		\ 'dir': '~/kyopro/library',
		\ 'options': '--border --preview "bat  --color=always --style=header,grid --line-range :100 {}"',
		\ 'down': '40%'
		\ })
endfunction


" vim-gitgutter
let g:gitgutter_override_sign_column_highlight = 0
highlight SignColumn ctermbg=black
highlight GitGutterAdd ctermfg=green
highlight GitGutterChange ctermfg=blue
highlight GitGutterDelete ctermfg=red
set updatetime=2000

" Library paste
nnoremap <C-L> :<C-u>call<Space>LibraryPaste()<CR>
inoremap <C-L> <Esc>:<C-u>call<Space>LibraryPaste()<CR>
