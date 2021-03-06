/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_UI_MENU
#define CHECKHEADER_SLIB_UI_MENU

#include "definition.h"

#include "../core/object.h"
#include "../core/string.h"
#include "../core/function.h"
#include "../graphics/bitmap.h"

#include "event.h"

namespace slib
{

	class Menu;
	
	class MenuItem : public Object
	{
		SLIB_DECLARE_OBJECT
		
	protected:
		MenuItem();
		
		~MenuItem();

	public:
		Ref<Menu> getParent() const;
		
		String getText() const;
		
		virtual void setText(const String& text);
		
		const KeycodeAndModifiers& getShortcutKey() const;
		
		virtual void setShortcutKey(const KeycodeAndModifiers& km);
		
		const KeycodeAndModifiers& getSecondShortcutKey() const;
		
		virtual void setSecondShortcutKey(const KeycodeAndModifiers& km);
		
		sl_bool isEnabled() const;
		
		virtual void setEnabled(sl_bool flag);
		
		sl_bool isChecked() const;
		
		virtual void setChecked(sl_bool flag);
		
		Ref<Bitmap> getIcon() const;
		
		virtual void setIcon(const Ref<Bitmap>& icon);
		
		Ref<Bitmap> getCheckedIcon() const;
		
		virtual void setCheckedIcon(const Ref<Bitmap>& icon);
		
		Ref<Menu> getSubmenu() const;
		
		virtual void setSubmenu(const Ref<Menu>& menu);
		
		Function<void()> getAction() const;
		
		virtual void setAction(const Function<void()>& action);
		
		virtual sl_bool isSeparator() const;
		
		static Ref<MenuItem> createSeparator();
		
		sl_bool processShortcutKey(const KeycodeAndModifiers& km);
		
	protected:
		WeakRef<Menu> m_parent;
		
		AtomicString m_text;
		KeycodeAndModifiers m_shortcutKey;
		KeycodeAndModifiers m_secondShortcutKey;
		sl_bool m_flagEnabled;
		sl_bool m_flagChecked;
		AtomicRef<Bitmap> m_icon;
		AtomicRef<Bitmap> m_checkedIcon;
		AtomicRef<Menu> m_submenu;
		AtomicFunction<void()> m_action;
		
	};
	
	class MenuItemParam
	{
	public:
		String text;
		KeycodeAndModifiers shortcutKey;
		KeycodeAndModifiers secondShortcutKey;
		sl_bool flagEnabled;
		sl_bool flagChecked;
		Ref<Bitmap> icon;
		Ref<Bitmap> checkedIcon;
		Ref<Menu> submenu;
		Function<void()> action;
		
	public:
		MenuItemParam();
		
		~MenuItemParam();

	};
	
	class Menu : public Object
	{
		SLIB_DECLARE_OBJECT
		
	protected:
		Menu();
		
		~Menu();

	public:
		static Ref<Menu> create();
		
		sl_uint32 getMenuItemsCount() const;
		
		Ref<MenuItem> getMenuItem(sl_uint32 index) const;
		
		virtual Ref<MenuItem> addMenuItem(const MenuItemParam& param) = 0;
		
		virtual Ref<MenuItem> insertMenuItem(sl_uint32 index, const MenuItemParam& param) = 0;
		
		virtual Ref<MenuItem> addSeparator() = 0;
		
		virtual Ref<MenuItem> insertSeparator(sl_uint32 index) = 0;
		
		virtual void removeMenuItem(sl_uint32 index) = 0;
		
		virtual void removeMenuItem(const Ref<MenuItem>& item) = 0;
		
		virtual void show(sl_ui_pos x, sl_ui_pos y) = 0;
		
		void show(const UIPoint& pt);
		
		Ref<MenuItem> addMenuItem(const String& title);
		
		Ref<MenuItem> addMenuItem(const String& title, const Ref<Bitmap>& icon);
		
		Ref<MenuItem> addMenuItem(const String& title, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon);
		
		Ref<MenuItem> addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey);
		
		Ref<MenuItem> addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey, const Ref<Bitmap>& icon);
		
		Ref<MenuItem> addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon);
		
		Ref<MenuItem> addSubmenu(Ref<Menu>& submenu, const String& title);
		
		Ref<MenuItem> addSubmenu(Ref<Menu>& submenu, const String& title, const Ref<Bitmap>& icon);
		
		Ref<MenuItem> addSubmenu(Ref<Menu>& submenu, const String& title, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon);
		
		sl_bool processShortcutKey(const KeycodeAndModifiers& km);
		
	protected:
		CList< Ref<MenuItem> > m_items;
		
	};

}

#endif
