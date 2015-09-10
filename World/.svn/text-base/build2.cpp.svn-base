//三单色电光源 一球
void World::build()
{

	int num_samples = 4;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_pixel_size(0.5); //关键！
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);

	ambient_ptr = new Ambient;


	ambient_ptr->scale_radiance(2.);
			
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(0, 360, 500);
	camera_ptr->set_lookat(0, 0, 0);
	camera_ptr->set_view_distance(850);     
	camera_ptr->compute_uvw(); 
	set_camera(camera_ptr);
		
	

	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(60, 200, 40); 
	light_ptr1->set_color(1, 0, 0);				// red
	light_ptr1->scale_radiance(5.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-60, 200, 40); 
	light_ptr2->set_color(0, 1, 0);				// green
	light_ptr2->scale_radiance(5.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(0, 200, -60); 
	light_ptr3->set_color(0, 0, 1);				// blue
	light_ptr3->scale_radiance(5.0);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	


	
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.2); 
	matte_ptr1->set_kd(0.8); 
	matte_ptr1->set_cd(0.5,0.5,0.5);
		
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0,70,0),27);  
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);

	
	// ground plane
	//
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.0); 
	matte_ptr2->set_kd(0.35);
	matte_ptr2->set_cd(0.7,0.7,0.7); 	
	
	Plane* plane_ptr = new Plane(Point3D(0, -3, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);


}
