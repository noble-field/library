syntax on

" backspace
set backspace=indent,eol,start

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
inoremap <C-v> <C-o>p
inoremap <C-BS> <Esc>dba

" Indent Line(s)
nnoremap <Tab> >>
nnoremap <S-Tab> <<
inoremap <S-Tab> <C-o><<
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

" Select Word
nnoremap ww viw

" Save
nnoremap ss :w<CR>

" fzf
set rtp+=~/.fzf
nnoremap <C-P> :Files<CR>
inoremap <C-P> <Esc>:Files<CR>

" vim-gitgutter
let g:gitgutter_override_sign_column_highlight = 0
highlight SignColumn ctermbg=black
highlight GitGutterAdd ctermfg=green
highlight GitGutterChange ctermfg=blue
highlight GitGutterDelete ctermfg=red
set updatetime=300

" Library paste
function! LibraryPaste()
	call fzf#run({
		\ 'sink': 'read',
		\ 'dir': '~/kyopro/library',
		\ 'options': '--border --preview "bat  --color=always --style=header,grid --line-range :100 {}"',
		\ 'down': '40%'
		\ })
endfunction

nnoremap <C-L> :<C-u>call<Space>LibraryPaste()<CR>
inoremap <C-L> <Esc>:<C-u>call<Space>LibraryPaste()<CR>

" coc-nvim settings
set encoding=utf-8
set hidden
set nobackup
set nowritebackup

set shortmess+=c

if has("nvim-0.5.0") || has("patch-8.1.1564")
  " Recently vim can merge signcolumn and number column into one
  set signcolumn=number
else
  set signcolumn=yes
endif

inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

function! s:check_back_space() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

if has('nvim')
  inoremap <silent><expr> <c-space> coc#refresh()
else
  inoremap <silent><expr> <c-@> coc#refresh()
endif

inoremap <silent><expr> <cr> pumvisible() ? coc#_select_confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

nmap <silent> [g <Plug>(coc-diagnostic-prev)
nmap <silent> ]g <Plug>(coc-diagnostic-next)

nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)

nnoremap <silent> K :call <SID>show_documentation()<CR>

function! s:show_documentation()
  if (index(['vim','help'], &filetype) >= 0)
    execute 'h '.expand('<cword>')
  elseif (coc#rpc#ready())
    call CocActionAsync('doHover')
  else
    execute '!' . &keywordprg . " " . expand('<cword>')
  endif
endfunction

nmap <leader>rn <Plug>(coc-rename)

command! -nargs=0 Format :call CocAction('format')

" popup colors
hi Pmenu ctermbg=white ctermfg=black
hi PmenuSel ctermbg=cyan ctermfg=black

" clpping command
function! ClipSource(path)
  call system('win32yank.exe -i < ' . a:path)
  echo a:path . ' clipped.'
endfunction

command! -nargs=0 Clip :call ClipSource(expand('%:p'))
nnoremap cc :Clip<CR>

" testing command
function! CompileSource()
  redraw
  echo 'compiling...'
  call system('g++ -O2 '.expand('%:p'))
endfunction

autocmd ColorScheme * hi MyPopupColor ctermbg=black

function! ResultFilter(winid, key)
  if a:key == 'q'
	call popup_close(a:winid)
  elseif a:key == 'd'
    
  endif
  return 0
endfunction

function! TestSource(...)
  redraw
  echo 'running...'
  if a:0 >= 1
	let l:result = split(system(expand('./a.out < ' . a:1)), "\n")
	call popup_create(l:result, #{
	  \ border: [], minwidth: winwidth(0)/2, minheight: &lines/2,
	  \ maxwidth: winwidth(0)/2, maxheight: &lines-4, scrollbar: 1, padding: [0,1,0,1],
	  \ highlight: 'MyPopupColor', filter: 'ResultFilter', close: 'click'
      \ })
  else
	let l:result = split(system(expand('./a.out < in')), "\n")
    call popup_create(l:result, #{ 
	  \ border: [], minwidth: winwidth(0)/2, minheight: &lines/2,
	  \ maxwidth: winwidth(0)/2, maxheight: &lines-4, scrollbar: 1, padding: [0,1,0,1],
	  \ highlight: 'MyPopupColor', filter: 'ResultFilter', close: 'click'
      \ })
  endif
  redraw
  echo 'complete.'
endfunction

function! CompileAndTest(...)
  call CompileSource()
  if a:0 >= 1
    call TestSource(a:1)
  else
	call TestSource()
  endif
endfunction

command! -nargs=? CTest :call CompileAndTest(<f-args>)
command! -nargs=? Test :call TestSource(<f-args>)

nnoremap <F5> :CTest<CR>
nnoremap <F9> :Test<CR>

function! ReplaceClip()
  0,$d
  let l:text = split(system('win32yank.exe -o'), "\r\n")
  call append(0, text)
endfunction

function! AppendClip()
  let l:text = split(system('win32yank.exe -o'), "\r\n")
  call append(".", text)
endfunction

nnoremap aa :call ReplaceClip()<CR>
nnoremap bp :call AppendClip()<CR>
