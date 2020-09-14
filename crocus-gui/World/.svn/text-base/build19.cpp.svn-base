//28.6(b) ÕÛÉä²âÊÔÍ¼ boring

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);	
	vp.set_max_depth(1);
	
	background_color = white;
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
		
	Pinhole* pinhole_ptr = new Pinhole;	
	pinhole_ptr->set_eye(0, 0, 500);   
	pinhole_ptr->set_lookat(-3, 0, 0);    
	pinhole_ptr->set_view_distance(30000000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
		
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0); 
	dielectric_ptr->set_ks(0.2);  
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(white);
	dielectric_ptr->set_cf_out(white);
		
	Sphere* sphere_ptr1 = new Sphere(Point3D(), 3);
	sphere_ptr1->set_material(dielectric_ptr);
	add_object(sphere_ptr1);		
}


