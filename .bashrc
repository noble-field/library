source ~/.git-prompt.sh

function __prompt_git_part(){
	git_prompt_string=$(__git_ps1 "%s")
	if [ -n  "$git_prompt_string" ]; then
		printf '\e[92;105m\e[30m %s \e[95;49m' $git_prompt_string
	else
		printf '\e[92;49m'
	fi
}

export PS1='\e[30;107m\] \D{%m/%d %H:%M} \[\e[97;102m\]\[\e[30m\] \W $(__prompt_git_part)\[\e[0m\] '
