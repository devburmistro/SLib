/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

namespace slib
{

	SLIB_INLINE MacAddress::MacAddress(const MacAddress& other) noexcept = default;

	SLIB_INLINE MacAddress& MacAddress::operator=(const MacAddress& other) noexcept = default;


	SLIB_INLINE const MacAddress& MacAddress::zero() noexcept
	{
		return *(reinterpret_cast<MacAddress const*>(&_zero));
	}
	
	SLIB_INLINE sl_bool MacAddress::isZero() const noexcept
	{
		return m[0] == 0 && m[1] == 0 && m[2] == 0 && m[3] == 0 && m[4] == 0 && m[5] == 0;
	}
	
	SLIB_INLINE sl_bool MacAddress::isNotZero() const noexcept
	{
		return m[0] != 0 || m[1] != 0 || m[2] != 0 || m[3] != 0 || m[4] != 0 || m[5] != 0;
	}
	
	SLIB_INLINE const MacAddress& MacAddress::getBroadcast() noexcept
	{
		return *(reinterpret_cast<MacAddress const*>(&_broadcast));
	}
	
	SLIB_INLINE sl_bool MacAddress::isBroadcast() const noexcept
	{
		return m[0] == 255 && m[1] == 255 && m[2] == 255 && m[3] == 255 && m[4] == 255 && m[5] == 255;
	}
	
	SLIB_INLINE sl_bool MacAddress::isNotBroadcast() const noexcept
	{
		return m[0] != 255 || m[1] != 255 || m[2] != 255 || m[3] != 255 || m[4] != 255 || m[5] != 255;
	}
	
	SLIB_INLINE sl_bool MacAddress::isMulticast() const noexcept
	{
		return (m[0] & 1);
	}
	
	SLIB_INLINE sl_bool MacAddress::isNotMulticast() const noexcept
	{
		return (m[0] & 1) == 0;
	}

	SLIB_INLINE sl_bool MacAddress::operator==(const MacAddress& other) const noexcept
	{
		return m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5];
	}
	
	SLIB_INLINE sl_bool MacAddress::operator!=(const MacAddress& other) const noexcept
	{
		return m[0] != other.m[0] || m[1] != other.m[1] || m[2] != other.m[2] || m[3] != other.m[3] || m[4] != other.m[4] || m[5] != other.m[5];
	}

}
