__kernel void example (int width, int height, int offset, __write_only image2d_t glTexture) {


  int x = get_global_id( 0 );
  int y = get_global_id( 1 );

  int2 l_pos = (int2)((get_local_id( 0 ) + offset) % get_local_size( 0 ), (get_local_id( 1 ) + offset) % get_local_size( 1 ));

  float r = (float)(l_pos.x % get_local_size(0)) / (float)get_local_size( 0 );
  float g = (float)l_pos.y / (float)get_local_size(1);

  // Compute the color from the local id. 
  float4 color = (float4)(r, g, 0.0f, 1.0f);

	write_imagef(glTexture, (int2)(x, y), color);
}