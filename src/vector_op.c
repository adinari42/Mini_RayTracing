/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:44:19 by miahmadi          #+#    #+#             */
/*   Updated: 2023/01/18 16:23:57 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vectorSubtract(t_vector v1, t_vector v2)
{
  t_vector	res;

  res.x = v1.x - v2.x;
  res.y = v1.y - v2.y;
  res.z = v1.z - v2.z;
  return (res);
}

t_vector	vectorAdd(t_vector v1, t_vector v2)
{
  t_vector	res;

  res.x = v1.x + v2.x;
  res.y = v1.y + v2.y;
  res.z = v1.z + v2.z;
  return (res);
}

t_vector	vectorScale(t_vector v, double s)
{
  t_vector	res;

  res.x = v.x * s;
  res.y = v.y * s;
  res.z = v.z * s;
  return (res);
}

t_vector	vectorNormalize(t_vector v)
{
  double length;

  length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length > 0) {
    v.x /= length;
    v.y /= length;
    v.z /= length;
  }
  return (v);
}

double vectorDotProduct(t_vector v1, t_vector v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector vectorProject(t_vector v1, t_vector v2)
{
  double	dot;
  double	square;

  dot = vectorDotProduct(v1, v2);
  square = vectorDotProduct(v2, v2);
  return vectorScale(v2, dot / square);
}
