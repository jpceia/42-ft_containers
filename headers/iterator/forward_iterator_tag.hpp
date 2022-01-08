/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator_tag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:25:11 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:17:31 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARD_ITERATOR_TAG_HPP
# define FORWARD_ITERATOR_TAG_HPP

# include "input_iterator_tag.hpp"

namespace ft
{
    struct forward_iterator_tag : public input_iterator_tag {};
}

#endif
