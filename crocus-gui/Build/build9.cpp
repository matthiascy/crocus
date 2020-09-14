//Bunny9

void 												
World::build(void) {
	int num_samples = 4;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);	
	
	tracer_ptr = new RayCast(this);
	
	background_color = black;

	Pinhole* pinhole_ptr = new Pinhole;	
	pinhole_ptr->set_eye(0, 40, 100);
	//pinhole_ptr->set_lookat(-0.5, 0, 0); //for golden-fish;
	pinhole_ptr->set_lookat(-2, 8, 0);   //for bunny;
	pinhole_ptr->set_view_distance(1600);  	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
		
	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(0.75, 0.5, -0.15);     
	directional_ptr->scale_radiance(2.0); 
	directional_ptr->set_shadows(true);
	add_light(directional_ptr);
	
	Phong* phong_ptr1 = new Phong;			
	phong_ptr1->set_ka(0.4); 
	phong_ptr1->set_kd(0.8);
	phong_ptr1->set_cd(1.0, 0.2, 0.0); 
	phong_ptr1->set_ks(0.5); 
	phong_ptr1->set_cs(1.0, 1.0, 0.0);
	phong_ptr1->set_exp(50.0);
	
	char* file_name = "c:\\bunny.ply";
//	const char* file_name = "goldfish_high_res.ply";
	Grid* grid_ptr = new Grid(new Mesh);
//	grid_ptr->read_flat_triangles(file_name);		
	grid_ptr->read_smooth_triangles(file_name);		
	grid_ptr->set_material(phong_ptr1);    
	grid_ptr->setup_cells();
	add_object(grid_ptr);
}


