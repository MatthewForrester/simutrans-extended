/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

 #include <string.h>
 #include "industrial_data.h"
 #include "../simworld.h"

 industrial_data_t::industrial_data_t() :
    gui_frame_t( "Industrial data calculations" )
{
    set_table_layout(1,0);
    target_industry_density_lb.buf().printf( "Target industry density: %u", world()->get_target_industry_density() );
    target_industry_density_lb.update();
    add_component(&target_industry_density_lb);
    actual_industry_density_lb.buf().printf( "Actual industry density: %u", world()->get_actual_industry_density() );
    actual_industry_density_lb.update();
    add_component(&actual_industry_density_lb);    
    sint64 estimated_industry_density_proportion = ( ( (world()->get_actual_industry_density() * 1000000ll) ) / world()->get_finance_history_month( 0, karte_t::player_cost::WORLD_CITIZENS ) );
    estimated_industry_density_proportion_lb.buf().printf( "Estimated industry_density_proportion after next revision: %i", estimated_industry_density_proportion );
    estimated_industry_density_proportion_lb.update();
    add_component( &estimated_industry_density_proportion_lb );
    reset_min_windowsize();
	set_windowsize(get_min_windowsize());
}