%{
int num_lines = 0;
int num_chars = 0;
%}

%option noyywrap
%%
\n      ++num_lines; ++num_chars;
.       ++num_chars;
