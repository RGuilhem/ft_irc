/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Botty.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:02:06 by graux             #+#    #+#             */
/*   Updated: 2023/12/06 19:04:20 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Botty.hpp"

Botty::Botty(void)
{
}

Botty::~Botty(void)
{
}

std::string	Botty::greet(void) const
{
	return ("Hello I'm botty you can send me a /help to see what I can do!");
}

std::string	Botty::getNickname(void) const
{
	return ("botty");
}
