/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Botty.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:02:10 by graux             #+#    #+#             */
/*   Updated: 2023/12/06 19:02:11 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOTTY_HPP
# define BOTTY_HPP

# include <string>

class Botty
{
	private:
	public:
		Botty(void);
		~Botty(void);

		std::string	greet(void) const;
		std::string	getNickname(void) const;
};

#endif
