/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: brey-gal <brey-gal@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 19:01:20 by brey-gal     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/20 19:01:20 by brey-gal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_LIBFT_H
# define FDF_LIBFT_H

# include "../includes/doom.h"

void		ft_puterror(char *str);
void		ft_putstr(char *str);
char		*ft_strnew(size_t size);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
int			ft_atoi(char const *str);
char		*ft_itoa(int n);
int			get_nb(char *line);

#endif
