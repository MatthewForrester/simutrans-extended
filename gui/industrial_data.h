/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef INDUSTRIAL_DATA_H
#define INDUSTRIAL_DATA_H

#include "gui_frame.h"
#include "components/gui_label.h"

// A simple window to display the industrial density calculations
class industrial_data_t : public gui_frame_t
{
    public:
        industrial_data_t();
    private:
        // TODONOW: Remove this if not longer needed for testing
        // gui_label_buf_t base_pathing_counter_lb;
        gui_label_buf_t target_industry_density_lb;
        gui_label_buf_t actual_industry_density_lb;
        gui_label_buf_t estimated_industry_density_proportion_lb;
};

#endif