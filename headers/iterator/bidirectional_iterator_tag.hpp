/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator_tag.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:26:43 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:17:15 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_TAG_HPP
# define BIDIRECTIONAL_ITERATOR_TAG_HPP

# include "forward_iterator_tag.hpp"

namespace ft
{
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
}

#endif
