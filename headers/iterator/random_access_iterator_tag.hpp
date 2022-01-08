/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator_tag.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:26:21 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:11:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_TAG_HPP
# define RANDOM_ACCESS_ITERATOR_TAG_HPP

# include "bidirectional_iterator_tag.hpp"

namespace ft
{
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}

#endif
