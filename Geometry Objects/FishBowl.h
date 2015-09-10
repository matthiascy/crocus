#ifndef __FISH_BOWL__
#define __FISH_BOWL__


#include "Compound.h"

class FishBowl: public Compound
{
	public:
		
		FishBowl(void);   							

		FishBowl(	const double _inner_radius, 
					const double _glass_thickness,
					const double _water_depth,
					const double _meniscus_radius,
					const double _opening_angle);

		FishBowl(const FishBowl& fb); 				
		
		virtual FishBowl* clone(void) const;

		virtual FishBowl& operator= (const FishBowl& rhs);		
		
		virtual ~FishBowl(void); 
		
		void build_components(void);
		
		void set_glass_air_material(Material* m_ptr);
		
		void set_water_air_material(Material* m_ptr); 
		
		void set_water_glass_material(Material* m_ptr); 
		
	protected:
	
		double inner_radius;		// radius of the inside glass surface
		double glass_thickness;
		double water_depth; 		// measured from the bottom of the water-glass boundary		
		double meniscus_radius;
		double opening_angle;		// specifies how wide the opening is at the top (alpha in Figure 28.40(a))
};

#endif
