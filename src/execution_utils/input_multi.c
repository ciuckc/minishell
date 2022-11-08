/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:30 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 13:10:33 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//./minishell < infile cat | wc > outfile
t_token	*get_test_input(void)
{
	t_token	*top;
	t_token	*node1;
	t_token	*node2;
	t_token	*node3;
	t_token	*node4;
	t_token	*node5;
	t_token	*node6;
	t_token	*node7;
	t_token	*node8;
	// t_token	*node9;
	// t_token	*node10;
	// t_token	*node11;

	/* < Makefile cat | wc -w >> testing/outfile */

	/* test with EMPTY between two PIPEs */
	top = NULL;
	node1 = malloc(sizeof(t_token));
	node1->token_type = LESS;
	node1->content = ft_substr("<", 0, 1);
	node2 = malloc(sizeof(t_token));
	node2->token_type = WORD;
	node2->content = ft_substr("infile", 0, 6);
	node3 = malloc(sizeof(t_token));
	node3->token_type = WORD;
	node3->content = ft_substr("cat", 0, 3);
	node4 = malloc(sizeof(t_token));
	node4->token_type = PIPE;
	node4->content = ft_substr("|", 0, 1);
	node5 = malloc(sizeof(t_token));
	node5->token_type = WORD;
	node5->content = ft_substr("cat", 0, 3);
	node6 = malloc(sizeof(t_token));
	node6->token_type = PIPE;
	node6->content = ft_substr("|", 0, 1);
	node7 = malloc(sizeof(t_token));
	node7->token_type = WORD;
	node7->content = ft_substr("wc", 0, 2);
	node8 = malloc(sizeof(t_token));
	node8->token_type = WORD;
	node8->content = ft_substr("-l", 0, 2);
	// node9 = malloc(sizeof(t_token));
	// node9->token_type = GREAT;
	// node9->content = ft_substr(">", 0, 1);
	// node10 = malloc(sizeof(t_token));
	// node10->token_type = WORD;
	// node10->content = ft_substr("outfile", 0, 7);
	// node6 = malloc(sizeof(t_token));
	// node6->token_type = GRT_TH;
	// node6->content = ft_substr(">", 0, 2);
	// node7 = malloc(sizeof(t_token));
	// node7->token_type = WORD;
	// node7->content = ft_substr("testing/newfile", 0, 15);
	// node7 = malloc(sizeof(t_token));
	// node7->token_type = WORD;
	// node7->content = ft_substr("env", 0, 3);
	// node8 = malloc(sizeof(t_token));
	// node8->token_type = DGRT_TH;
	// node8->content = ft_substr(">>", 0, 1);
	// node9 = malloc(sizeof(t_token));
	// node9->token_type = WORD;
	// node9->content = ft_substr("testing/newfile.txt", 0, 19);
	// node10 = malloc(sizeof(t_token));
	// node10->token_type = WORD;
	// node10->content = ft_substr("xoxo", 0, 4);
	// node11 = malloc(sizeof(t_token));
	// node11->token_type = WORD;
	// node11->content = ft_substr("testing/outfile.txt", 0, 20);
	top = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	// node8->next = node9;
	// node9->next = node10;
	// node10->next = node11;
	node8->next = NULL;
	return (top);
}
