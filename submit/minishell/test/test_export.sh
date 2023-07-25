./minishell <<HEREDOC >minishell_output.txt 2>&-
export ASDF=$ASDG
env
HEREDOC
minishell_status=$?

bash <<HEREDOC >bash_output.txt 2>&-
export ASDF=$ASDG
env
HEREDOC
bash_status=$?

# Compare output files
diff -y minishell_output.txt bash_output.txt

# Compare exit statuses
if [ $minishell_status -eq $bash_status ]; then
    echo "Exit statuses are the same."
else
    echo "Exit statuses are different."
fi
