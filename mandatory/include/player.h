/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:38:32 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/25 02:38:33 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

int		player_move_forward(t_map *map);
int		player_move_backward(t_map *map);
int		player_move_left(t_map *map);
int		player_move_right(t_map *map);
void	update_player_old_pos(t_map *map);

#endif