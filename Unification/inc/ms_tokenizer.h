#ifndef MS_TOKENIZER_H
# define MS_TOKENIZER_H

// MS tokenizer.
t_token_list	*ms_tokenize(char *src, t_error *error);

// MS tokenizer word.
void			tokenize_word(t_lexer *lexer, t_token_list **token_list, t_error *error);

// MS tokenizer utils.
bool			ms_is_whitespace(char c);
bool			ms_is_metacharacter(char c);


#endif /* MS_TOKENIZER_H */