/* DisplayVSlider.hpp
 * Copyright (C) 2018  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BWIDGETS_DISPLAYVSLIDER_HPP_
#define BWIDGETS_DISPLAYVSLIDER_HPP_

#include "RangeWidget.hpp"
#include "Label.hpp"
#include "VSlider.hpp"

#define BWIDGETS_DEFAULT_DISPLAYVSLIDER_WIDTH 24.0
#define BWIDGETS_DEFAULT_DISPLAYVSLIDER_HEIGHT BWIDGETS_DEFAULT_VSLIDER_HEIGHT

namespace BWidgets
{

/**
 * Class BWidgets::DisplayVSlider
 *
 * Composite RangeWidget consisting of a vertical slider and a label widget.
 */
class DisplayVSlider : public RangeWidget
{
public:
	DisplayVSlider ();
	DisplayVSlider (const double x, const double y, const double width, const double height, const std::string& name,
			  	  	  	  	 const double value, const double min, const double max, const double step,
							 const std::string& valueFormat);

	/**
	 * Creates a new (orphan) slider and copies the slider properties from a
	 * source slider. This method doesn't copy any parent or child widgets.
	 * @param that Source slider
	 */
	DisplayVSlider (const DisplayVSlider& that);

	~DisplayVSlider ();

	/**
	 * Assignment. Copies the slider properties from a source slider and keeps
	 * its name and its position within the widget tree. Emits an expose event
	 * if the widget is visible and a value changed event.
	 * @param that Source slider
	 */
	DisplayVSlider& operator= (const DisplayVSlider& that);

	/**
	 * Changes the value of the widget and keeps it within the defined range.
	 * Passes the value to its predefined child widgets.
	 * Emits a value changed event and (if visible) an expose event.
	 * @param val Value
	 */
	virtual void setValue (const double val) override;

	/**
	 * Sets the lower limit. Forces the value into the new range. Passes the
	 * min to its predefined child widgets. Emits a value changed event (if
	 * value changed) and (if visible) an expose event.
	 * @param min Lower limit
	 */
	virtual void setMin (const double min) override;

	/**
	 * Sets the upper limit. Forces the value into the new range. Passes the
	 * max to its predefined child widgets. Emits a value changed event (if
	 * value changed) and (if visible) an expose event.
	 * @param max Upper limit
	 */
	virtual void setMax (const double min) override;

	/**
	 * Sets the increment steps for the value. Passes the
	 * increment to its predefined child widgets.
	 * @param step Increment steps.
	 */
	virtual void setStep (const double step);

	/**
	 * Sets the value output format.
	 * @valueFormat Format of the output in printf standard for type double.
	 */
	void setValueFormat (const std::string& valueFormat);

	/**
	 * Gets the value output format.
	 * @return Format of the output in printf standard for type double.
	 */
	std::string getValueFormat () const;



	/**
	 * Gets (a pointer to) the slider widget for direct access
	 * @return Pointer to BWidgets::VSlider
	 */
	VSlider* getSlider ();

	/**
	 * Gets (a pointer to) the Label for direct access.
	 * @return Pointer to the label
	 */
	Label* getValueDisplay ();

	/**
	 * Calls a redraw of the widget and calls postRedisplay () if the the
	 * Widget is visible.
	 * This method should be called if the widgets properties are indirectly
	 * changed.
	 */
	virtual void update () override;

	/**
	 * Scans theme for widget properties and applies these properties.
	 * @param theme Theme to be scanned.
	 * 				For styles used see BWidgets::Dial::applyTheme and
	 * 				BWidgets::Label::applyTheme.
	 * @param name Name of the BStyles::StyleSet within the theme to be
	 * 		  	   applied.
	 */
	virtual void applyTheme (BStyles::Theme& theme);
	virtual void applyTheme (BStyles::Theme& theme, const std::string& name);

protected:
	static void redirectPostValueChanged (BEvents::Event* event);
	void updateChildCoords ();
	virtual void draw (const double x, const double y, const double width, const double height) override;

	VSlider slider;
	Label valueDisplay;

	std::string valFormat;
};

}

#endif /* BWIDGETS_DISPLAYVSLIDER_HPP_ */
