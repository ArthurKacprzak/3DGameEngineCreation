//
// Created by arthur on 05/11/2020.
//

#ifndef INC_3DGAMEENGINECREATION_VKTOOLS_HPP
#define INC_3DGAMEENGINECREATION_VKTOOLS_HPP

#include <iostream>

#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" <<  "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}


#endif //INC_3DGAMEENGINECREATION_VKTOOLS_HPP
