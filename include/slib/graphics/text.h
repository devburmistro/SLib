/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_GRAPHICS_TEXT
#define CHECKHEADER_SLIB_GRAPHICS_TEXT

#include "definition.h"

#include "constants.h"
#include "canvas.h"

#include "../core/string.h"
#include "../core/function.h"
#include "../math/rectangle.h"

namespace slib
{

	enum class TextItemType
	{
		Word = 0,
		Space = 10,
		Tab = 11,
		LineBreak = 20,
		Attach = 100
	};
	
	typedef sl_size sl_text_pos;
	
#define SLIB_TEXT_RANGE_NOT_FOUND SLIB_SIZE_MAX
	
	class SLIB_EXPORT TextRange
	{
	public:
		sl_text_pos location;
		sl_text_pos length;
		
	public:
		SLIB_INLINE constexpr TextRange() noexcept : location(SLIB_TEXT_RANGE_NOT_FOUND), length(0) {}
		
		SLIB_INLINE constexpr TextRange(sl_null_t) noexcept : location(SLIB_TEXT_RANGE_NOT_FOUND), length(0) {}
		
		SLIB_INLINE constexpr TextRange(sl_text_pos _location, sl_text_pos _length) noexcept : location(_location), length(_length) {}
		
		SLIB_INLINE constexpr TextRange(const TextRange& other) noexcept : location(other.location), length(other.length) {};
		
	public:
		SLIB_INLINE TextRange& operator=(const TextRange& other) noexcept
		{
			location = other.location;
			length = other.length;
			return *this;
		}
		
		SLIB_INLINE constexpr sl_bool operator==(const TextRange& other) const noexcept
		{
			return location == other.location && length == other.length;
		}
		
		SLIB_INLINE constexpr sl_bool operator!=(const TextRange& other) const noexcept
		{
			return location != other.location || length != other.length;
		}
		
		SLIB_INLINE constexpr sl_bool isNotFound() const noexcept
		{
			return location == SLIB_TEXT_RANGE_NOT_FOUND;
		}
		
	};
	
	class SLIB_EXPORT TextStyle : public Referable
	{
	public:
		AtomicRef<Font> font;
		Color textColor;
		Color backgroundColor;
		
	public:
		TextStyle() noexcept;
		
		~TextStyle() noexcept;

	};
	
	class SLIB_EXPORT TextItem : public Object
	{
		SLIB_DECLARE_OBJECT

	protected:
		TextItem(TextItemType type) noexcept;

		~TextItem() noexcept;
	
	public:
		TextItemType getType() noexcept;
		
		Ref<TextStyle> getStyle() noexcept;
		
		void setStyle(const Ref<TextStyle>& style) noexcept;
		
		Ref<Font> getFont() noexcept;
	
		Point getLayoutPosition() noexcept;

		void setLayoutPosition(const Point& pt) noexcept;

		Size getLayoutSize() noexcept;

		void setLayoutSize(const Size& size) noexcept;

		Rectangle getLayoutFrame() noexcept;

	protected:
		TextItemType m_type;
		AtomicRef<TextStyle> m_style;
		Point m_layoutPosition;
		Size m_layoutSize;

	};
	
	class SLIB_EXPORT TextWordItem : public TextItem
	{
		SLIB_DECLARE_OBJECT

	private:
		TextWordItem() noexcept;

		~TextWordItem() noexcept;

	public:
		static Ref<TextWordItem> create(const String16& text, const Ref<TextStyle>& style) noexcept;

	public:
		String16 getText() noexcept;

		void setText(const String16& text) noexcept;

		Size getSize() noexcept;
		
	private:
		AtomicString16 m_text;

		Ref<Font> m_fontCached;
		String16 m_textCached;
		sl_real m_widthCached;
		sl_real m_heightCached;

	};
	
	class SLIB_EXPORT TextSpaceItem : public TextItem
	{
		SLIB_DECLARE_OBJECT

	private:
		TextSpaceItem() noexcept;

		~TextSpaceItem() noexcept;

	public:
		static Ref<TextSpaceItem> create(const Ref<TextStyle>& style) noexcept;

	public:
		Size getSize() noexcept;

	};
	
	class SLIB_EXPORT TextTabItem : public TextItem
	{
		SLIB_DECLARE_OBJECT

	private:
		TextTabItem() noexcept;

		~TextTabItem() noexcept;

	public:
		static Ref<TextTabItem> create(const Ref<TextStyle>& style) noexcept;

	public:
		sl_real getHeight() noexcept;

	};
	
	class SLIB_EXPORT TextLineBreakItem : public TextItem
	{
		SLIB_DECLARE_OBJECT

	private:
		TextLineBreakItem() noexcept;

		~TextLineBreakItem() noexcept;

	public:
		static Ref<TextLineBreakItem> create(const Ref<TextStyle>& style) noexcept;

	public:
		sl_real getHeight() noexcept;

	};
	
	
	class SLIB_EXPORT TextAttachItem : public TextItem
	{
		SLIB_DECLARE_OBJECT

	public:
		TextAttachItem() noexcept;

		~TextAttachItem() noexcept;

	public:
		virtual Size getSize() noexcept = 0;

		virtual void setPosition(const Point& pos) noexcept = 0;

	};
	
	class TextParagraphLayoutParam
	{
	public:
		sl_real width;
		sl_real tabWidth;
		sl_real tabMargin;
		Alignment align;
		MultiLineMode multiLineMode;

	public:
		TextParagraphLayoutParam() noexcept;

		~TextParagraphLayoutParam() noexcept;

	};
	
	class SLIB_EXPORT TextParagraph : public Object
	{
		SLIB_DECLARE_OBJECT

	public:
		TextParagraph() noexcept;

		~TextParagraph() noexcept;

	public:
		void addText(const String16& text, const Ref<TextStyle>& style) noexcept;

		void layout(const TextParagraphLayoutParam& param) noexcept;

		void draw(Canvas* canvas, sl_real x, sl_real y) noexcept;

		sl_real getMaximumWidth() noexcept;

		sl_real getTotalHeight() noexcept;
		
		sl_real getPositionLength() noexcept;

	protected:
		CList< Ref<TextItem> > m_items;
		CList< Ref<TextItem> > m_layoutItems;
		sl_real m_maxWidth;
		sl_real m_totalHeight;
		sl_real m_positionLength;

	};
	
	class SLIB_EXPORT SimpleTextBox : public Object
	{
		SLIB_DECLARE_OBJECT

	public:
		SimpleTextBox() noexcept;

		~SimpleTextBox() noexcept;

	public:
		void update(const String& text, const Ref<Font>& font, sl_real width, sl_bool flagWrappingWidth, MultiLineMode multiLineMode, const Alignment& align) noexcept;

		void draw(Canvas* canvas, const String& text, const Ref<Font>& font, const Rectangle& frame, sl_bool flagWrappingWidth, MultiLineMode multiLineMode, const Alignment& align, const Color& color) noexcept;

		sl_real getContentWidth() noexcept;

		sl_real getContentHeight() noexcept;

	protected:
		Ref<TextParagraph> m_paragraph;

		String m_text;
		Ref<TextStyle> m_style;
		Ref<Font> m_font;
		sl_real m_width;
		MultiLineMode m_multiLineMode;
		Alignment m_align;

		sl_real m_contentWidth;
		sl_real m_contentHeight;

	};

}

#endif
