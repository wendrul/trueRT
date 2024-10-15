// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cyl_ops.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: agoodwin <agoodwin@42.edu.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/11/16 18:01:17 by agoodwin          #+#    #+#             */
// /*   Updated: 2020/09/24 01:40:11 by agoodwin         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
// #include "minirt.h"
//
// char *check_cone_args(t_parse_args parsed) {
//   float args[MAX_PARSE_FIGURE_ARGUMENTS];
//
//   ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
//   if (parsed.size < 11)
//     return ("Not enough arguments for a cone.");
//   if (args[3] > 1 || args[4] > 1 || args[5] > 1 || args[3] < -1 ||
//       args[4] < -1 || args[5] < -1)
//     return ("Cone orientation vector values not in range (-1, 1).");
//   if (args[6] < 0)
//     return ("Cone diameter is negative");
//   if (args[7] < 0)
//     return ("Cone height is negative");
//   if (args[8] > 255 || args[9] > 255 || args[10] > 255 || args[8] < 0 ||
//       args[9] < 0 || args[10] < 0)
//     return ("Invalid RGB values for cone (must be between 0 and 255).");
//   return (NULL);
// }
//
// t_cone create_cone(t_parse_args parsed)
// {
//     char *msg;
//     t_cone cone;
//
//     msg = check_cone_args(parsed);
//     if (msg != NULL)
//         clean_exit(1, msg);
//     cone = (t_cone)create_hcone(parsed);
//     cone.intersection = cone_intersection;
//     cone.get_normal_at = get_cone_normal_vector;
//     return (cone);
// }
//
// t_point cone_intersection(t_cone cone, t_vect ray, t_point start)
// {
//     t_circle bottom;
//     t_point cone_i;
//     t_point bottom_i;
//
//     bottom = cone;
//     bottom.normal = scale(cone.normal, -1);
//     cone_i = hcone_intersection(cone, ray, start);
//     bottom_i = circle_intersection(bottom, ray, start);
//     if (distance(cone_i, start) > distance(bottom_i, start))
//     {
//         return (bottom_i);
//     }
//     return (cone_i);
// }
//
//
// t_vect get_cone_normal_vector(t_vect inter, t_figure cone, t_point start)
// {
//     t_circle bottom;
//     t_point cone_i;
//     t_figure part_hit;
//
//     bottom = cone;
//     bottom.normal = scale(cone.normal, -1);
//     cone.get_normal_at = get_hcone_normal_vector;
//     bottom.get_normal_at = get_circle_normal_vector;
//     cone_i = hcone_intersection(cone, vector(start, inter), start);
//     
//     if (distance(cone_i, start) > distance(circle_intersection(bottom, vector(start, inter), start), start))
//         part_hit = bottom;
//     else
//         part_hit = cone;
//
//     return (part_hit.get_normal_at(inter, part_hit, start));
// }
//


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:01:17 by agoodwin          #+#    #+#             */
/*   Updated: 2024/10/14 19:08:35 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"
//
// char		*check_cone_args(t_parse_args parsed)
// {
// 	float args[MAX_PARSE_FIGURE_ARGUMENTS];
//
// 	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
// 	if (parsed.size < 9) // Cones need more arguments
// 		return ("Not enough arguments for a cone.");
// 	if (args[3] <= 0)
// 		return ("Cone height must be positive.");
// 	if (args[4] <= 0)
// 		return ("Cone angle must be positive.");
// 	if (args[5] > 255 || args[6] > 255 || args[7] > 255 ||
// 		args[5] < 0 || args[6] < 0 || args[7] < 0)
// 		return ("Invalid RGB values for cone (must be between 0 and 255).");
// 	return (NULL);
// }
//
// t_cone		create_cone(t_parse_args parsed)
// {
// 	t_cone		cone;
// 	char		*msg;
//
// 	msg = check_cone_args(parsed);
// 	if (msg != NULL)
// 		clean_exit(1, msg);
// 	cone.x = parsed.args[0];
// 	cone.y = parsed.args[1];
// 	cone.z = parsed.args[2];
// 	cone.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
// 	cone.length = parsed.args[3];
// 	cone.radius = parsed.args[4];
// 	cone.color = rgb_to_int(new_color(parsed.args[5],
// 					parsed.args[6], parsed.args[7]));
// 	cone.is_reflective = 0;
// 	if (parsed.size > 8)
// 		cone.is_reflective = parsed.args[8];
// 	cone.intersection = cone_intersection;
// 	cone.get_normal_at = get_cone_normal_vector;
// 	ft_memcpy(cone.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
// 	return (cone);
// }
//
// t_point		solve_equaa(t_polynome equa, t_vect result, t_vect ray, t_vect start)
// {
// 	float	t;
//
// 	if ((equa.delta = equa.b * equa.b - 4 * equa.a * equa.c) > 0)
// 	{
// 		equa.sqrt_delta = sqrt(equa.delta);
// 		t = ((-equa.b + equa.sqrt_delta) / (2 * equa.a)) * -1;
// 		if (t > 0)
// 		{
// 			result = new_vect(start.x + t * ray.x, start.y + t * ray.y,
// 							start.z + t * ray.z);
// 			return (result);
// 		}
// 		t = ((-equa.b - equa.sqrt_delta) / (2 * equa.a)) * -1;
// 		if (t > 0)
// 		{
// 			result = new_vect(start.x + t * ray.x, start.y + t * ray.y,
// 							start.z + t * ray.z);
// 			return (result);
// 		}
// 	}
// 	result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
// 	return (result);
// }
//
// t_point		cone_intersection(t_cone cone, t_vect ray, t_point start)
// {
// 	t_polynome	equa;
// 	t_vect		result;
// 	t_vect		subbed;
// 	float		k;
//
// 	result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
// 	subbed = subtract(cone.center, start);
// 	k = pow(tan(cone.radius), 2);
// 	equa.a = pow(ray.x, 2) + pow(ray.y, 2) - k * pow(ray.z, 2);
// 	equa.b = 2 * (ray.x * subbed.x + ray.y * subbed.y - k * ray.z * subbed.z);
// 	equa.c = pow(subbed.x, 2) + pow(subbed.y, 2) - k * pow(subbed.z, 2);
// 	return (solve_equaa(equa, result, ray, start));
// }
//
// t_vect		get_cone_normal_vector(t_vect inter, t_figure c, t_point start)
// {
// 	t_vect	normal;
// 	t_vect	to_center;
// 	float	m;
//
// 	to_center = subtract(inter, c.center);
// 	m = sqrt(pow(to_center.x, 2) + pow(to_center.y, 2));
// 	normal = new_vect(to_center.x / m, to_center.y / m, -c.length / m);
// 	if (dot(subtract(inter, start), normal) < 0)
// 		return (normal);
// 	else
// 		return (scale(normal, -1));
// }
//
//
//


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:01:17 by agoodwin          #+#    #+#             */
/*   Updated: 2024/10/14 17:55:50 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char *check_cone_args(t_parse_args parsed)
{
    float args[MAX_PARSE_FIGURE_ARGUMENTS];

    ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
    if (parsed.size < 11)
        return ("Not enough arguments for a cone.");
    if (args[3] > 1 || args[4] > 1 || args[5] > 1 ||
        args[3] < -1 || args[4] < -1 || args[5] < -1)
        return ("Cone orientation vector values not in range (-1, 1).");
    if (args[6] < 0)
        return ("Cone base radius is negative");
    if (args[7] < 0)
        return ("Cone height is negative");
    if (args[8] > 255 || args[9] > 255 || args[10] > 255 ||
        args[8] < 0 || args[9] < 0 || args[10] < 0)
        return ("Invalid RGB values for cone (must be between 0 and 255).");
    return (NULL);
}

t_cone create_cone(t_parse_args parsed)
{
    t_cone cone;
    char *msg;

    msg = check_cone_args(parsed);
    if (msg != NULL)
        clean_exit(1, msg);
    cone.x = parsed.args[0];
    cone.y = parsed.args[1];
    cone.z = parsed.args[2];
    cone.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
    cone.normal.x = parsed.args[3];
    cone.normal.y = parsed.args[4];
    cone.normal.z = parsed.args[5];
    cone.normal = normalize(cone.normal);
    cone.radius = parsed.args[6];
    cone.length = parsed.args[7];
    cone.color = rgb_to_int(new_color(parsed.args[8], parsed.args[9], parsed.args[10]));
    cone.is_reflective = 0;
    if (parsed.size > 11)
        cone.is_reflective = parsed.args[11];
    cone.intersection = cone_intersection;
    cone.get_normal_at = get_cone_normal_vector;
    ft_memcpy(cone.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
    return (cone);
}

t_point cone_intersection(t_cone cone, t_vect r, t_point s)
{
    t_polynome equa;
    t_vect v1;
    t_vect v2;
    float k;

    // k is the slope of the cone, relating length and radius
    k = cone.radius / cone.length;

    // Cone intersection calculation
    v1 = subtract(r, scale(cone.normal, dot(r, cone.normal)));
    v2 = subtract(s, cone.center);
    equa.a = dot(v1, v1) - (1 + k * k) * pow(dot(r, cone.normal), 2);
    equa.b = 2 * (dot(v1, v2) - (1 + k * k) * dot(r, cone.normal) * dot(v2, cone.normal));
    equa.c = dot(v2, v2) - (1 + k * k) * pow(dot(v2, cone.normal), 2);

    return solve_cone_equa(equa, cone, r, s);
}

t_point solve_cone_equa(t_polynome equa, t_figure cone, t_vect r, t_vect s)
{
    t_vect result;
    float t;

    if ((equa.delta = equa.b * equa.b - 4 * equa.a * equa.c) > EPSILON)
    {
        equa.sqrt_delta = sqrt(equa.delta);
        t = ((-equa.b + equa.sqrt_delta) / (2 * equa.a)) * -1;
        if (t > 0)
        {
            result = new_vect(s.x + t * r.x, s.y + t * r.y, s.z + t * r.z);
            t = dot(subtract(result, cone.center), cone.normal);
            if (t < cone.length && t > 0)
                return (result);
        }
        t = ((-equa.b - equa.sqrt_delta) / (2 * equa.a)) * -1;
        if (t > 0)
        {
            result = new_vect(s.x + t * r.x, s.y + t * r.y, s.z + t * r.z);
            t = dot(subtract(result, cone.center), cone.normal);
            if (t < cone.length && t > 0)
                return (result);
        }
    }
    result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
    return (result);
}

t_vect get_cone_normal_vector(t_vect inter, t_figure cone, t_point s)
{
    t_vect normal;
    t_vect u;
    float height_ratio;

    u = subtract(inter, cone.center);
    height_ratio = dot(u, cone.normal) / cone.length;
    normal = subtract(u, scale(cone.normal, height_ratio * (1 + cone.radius / cone.length)));
    normal = normalize(normal);

    if (dot(subtract(inter, s), normal) < 0)
        return (normal);
    else
        return (scale(normal, -1));
}

