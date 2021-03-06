/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#include <stdio.h>

#include "../simworld.h"
#include "../simevent.h"

#include "../dataobj/translator.h"

#include "../player/simplay.h"

#include "extend_edit.h"


static const char* numbers[] = { "0", "1", "2", "3" };

gui_rotation_item_t::gui_rotation_item_t(uint8 r) : gui_scrolled_list_t::const_text_scrollitem_t(NULL, SYSCOL_TEXT)
{
	rotation = r;

	if (rotation <= 3) {
		text = numbers[rotation];
	}
	else if (rotation == automatic) {
		text = translator::translate("auto");
	}
	else if (rotation == random) {
		text = translator::translate("random");
	}
	else {
		text = "";
	}
}


extend_edit_gui_t::extend_edit_gui_t(const char *name, player_t* player_) :
	gui_frame_t( name, player_ ),
	player(player_),
	info_text(&buf, D_BUTTON_WIDTH*4),
	scrolly(&info_text, true, true),
	scl(gui_scrolled_list_t::listskin, gui_scrolled_list_t::scrollitem_t::compare)
{
	is_show_trans_name = true;

	set_table_layout(2,0);
	set_force_equal_columns(true);
	set_alignment(ALIGN_LEFT | ALIGN_TOP);

	// left column
	add_table(1,0);
	// tab panel
	tabs.add_tab(&cont_left, translator::translate("Translation"));
	tabs.add_tab(&cont_left, translator::translate("Object"));
	tabs.add_listener(this);
	add_component(&tabs);

	cont_left.set_table_layout(1,0);
	cont_left.set_alignment(ALIGN_CENTER_H);
	// add stretcher element
	cont_left.new_component<gui_fill_t>();
	// init scrolled list
	scl.set_highlight_color(color_idx_to_rgb(player->get_player_color1()+1));
	cont_left.add_component(&scl);
	scl.set_selection(-1);
	scl.add_listener(this);
	scl.set_min_width( (D_DEFAULT_WIDTH-D_MARGIN_LEFT-D_MARGIN_RIGHT-2*D_H_SPACE)/2 );

	// add image
	cont_left.add_component(&building_image);

	end_table();

	// right column
	add_table(1,0);

	// add stretcher element
	cont_left.new_component<gui_fill_t>();

	bt_climates.init( button_t::square_state, "ignore climates");
	bt_climates.add_listener(this);
	add_component(&bt_climates);

	bt_timeline.init( button_t::square_state, "Use timeline start year");
	bt_timeline.pressed = welt->get_settings().get_use_timeline()&1;
	bt_timeline.add_listener(this);
	add_component(&bt_timeline);

	bt_obsolete.init( button_t::square_state, "Show obsolete");
	bt_obsolete.add_listener(this);
	add_component(&bt_obsolete);

	add_component(&cont_right);
	cont_right.set_table_layout(1,0);

	scrolly.set_visible(true);
	add_component(&scrolly);
	scrolly.set_min_width( (D_DEFAULT_WIDTH-D_MARGIN_LEFT-D_MARGIN_RIGHT-2*D_H_SPACE)/2 );
	end_table();

	set_resizemode(diagonal_resize);
}



/**
 * Mouse click are hereby reported to its GUI-Components
 */
bool extend_edit_gui_t::infowin_event(const event_t *ev)
{
	if(ev->ev_class == INFOWIN  &&  ev->ev_code == WIN_CLOSE) {
		change_item_info(-1);
	}
	return gui_frame_t::infowin_event(ev);
}



// resize flowtext to avoid horizontal scrollbar
void extend_edit_gui_t::set_windowsize( scr_size s )
{
	gui_frame_t::set_windowsize( s );
	info_text.set_width( scrolly.get_client().w );
}


bool extend_edit_gui_t::action_triggered( gui_action_creator_t *comp,value_t /* */)
{
	if (comp == &tabs) {
		// switch list translation or object name
		if (tabs.get_active_tab_index() == 0 && !is_show_trans_name) {
			// show translation list
			is_show_trans_name = true;
			fill_list( is_show_trans_name );
		}
		else if (tabs.get_active_tab_index() == 1 && is_show_trans_name) {
			// show object list
			is_show_trans_name = false;
			fill_list( is_show_trans_name );
		}
	}
	else if (comp == &scl) {
		// select an item of scroll list ?
		change_item_info(scl.get_selection());
	}
	else if(  comp==&bt_obsolete  ) {
		bt_obsolete.pressed ^= 1;
		fill_list( is_show_trans_name );
	}
	else if(  comp==&bt_climates  ) {
		bt_climates.pressed ^= 1;
		fill_list( is_show_trans_name );
	}
	else if(  comp==&bt_timeline  ) {
		bt_timeline.pressed ^= 1;
		fill_list( is_show_trans_name );
	}
	return true;
}


uint8 extend_edit_gui_t::get_rotation() const
{
	if (gui_rotation_item_t *item = dynamic_cast<gui_rotation_item_t*>( cb_rotation.get_selected_item() ) ) {
		return item->get_rotation();
	}
	return 0;
}
