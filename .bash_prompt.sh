# Color Tables
declare -A colors=(
	[reset]='\[\e[0m\]'
	[black]='\[\e[30m\]'
	[red]='\[\e[91m\]'
	[green]='\[\e[92m\]'
	[yellow]='\[\e[93m\]'
	[blue]='\[\e[94m\]'
	[magenta]='\[\e[95m\]'
	[cyan]='\[\e[96m\]'
	[gray]='\[\e[97m\]'
)
declare -A bg_colors=(
	[reset]='\[\e[49m\]'
	[black]='\[\e[40m\]'
	[red]='\[\e[101m\]'
	[green]='\[\e[102m\]'
	[yellow]='\[\e[103m\]'
	[blue]='\[\e[104m\]'
	[magenta]='\[\e[105m\]'
	[cyan]='\[\e[106m\]'
	[gray]='\[\e[107m\]'
)

function __transition {
	echo -n "${bg_colors[$2]}"
	if [ -n "$__last_bgcolor" ]; then
		echo -n "${colors[$__last_bgcolor]}"
	fi
	echo -n "${colors[$1]}"
	__last_bgcolor=$2
}

function __date_part {
	__transition $1 $2
	echo -n " \D{%m/%d %H:%M} "
}

function __dir_part {
	__transition $1 $2
	echo -n " \W "
}

function __git_part {
	branch=$(git rev-parse --abbrev-ref HEAD 2> /dev/null)
	if [ -n  "$branch" ]; then
		__transition $1 $2
		echo -n "  ${branch} "
	fi
}

function __end_of_prompt {
	__transition reset reset
	echo -n " "
	__last_bgcolor=""
}

function construct {
	__date_part black gray
	__dir_part black green
	__git_part black magenta
	__end_of_prompt
}

export PROMPT_COMMAND='export PS1=$(construct)'
