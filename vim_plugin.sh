# plugin directory
PLUGIN_PATH=~/.vim/pack/plugin/start
[ ! -d $PLUGIN_PATH ] && mkdir -p $PLUGIN_PATH
cd $PLUGIN_PATH

# vim-commentary
[ ! -d "${PLUGIN_PATH}/commentary" ] && git clone https://tpope.io/vim/commentary.git

# vim-airline
[ ! -d "${PLUGIN_PATH}/vim-airline" ] && git clone https://github.com/vim-airline/vim-airline.git
[ ! -d "${PLUGIN_PATH}/vim-airline-themes" ] && git clone https://github.com/vim-airline/vim-airline-themes.git

# vim-fugitive
[ ! -d "${PLUGIN_PATH}/vim-fugitive" ] && git clone https://tpope.io/vim/fugitive.git

# vim-gitgutter
[ ! -d "${PLUGIN_PATH}/vim-gitgutter" ] && git clone https://github.com/airblade/vim-gitgutter.git

# fzf.vim
if [ ! -d "~/.fzf" ] then;
	git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
	~/.fzf/install
fi

[ ! -d "${PLUGIN_PATH}/fzf.vim" ] && git clone https://github.com/junegunn/fzf.vim.git

# coc.nvim
if [ ! -d  "${PLUGIN_PATH}/coc.nvim" ] then;
	git clone https://github.com/neoclide/coc.nvim.git
	echo "To install nodejs, run\'curl -sL install-node.now.sh/lts | bash\'"
	echo "To complete coc.nvim, run\'yarn install --frozen-lockfile\'"
fi
