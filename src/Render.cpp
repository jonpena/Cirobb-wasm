
struct vertex {
  real x, y, r, g, b, a;
};


void DrawCircle(const Shape* shape)
{
  const real R = 0.4f, G = 0.4f, B = 0.4f, A = 0.4f;

	const RigidBody* body = shape->body;

	const int  countVerts = 40; // Number of Vertices
	const real valueVerts = PI * 2 / countVerts;
	vertex verts[countVerts + 1];
 
	const real radius = shape->radius;

	for(int i = 0; i <= countVerts; i++) // RADIAN [0, 2PI] --> DEGREE [0, 360]
	{
	  verts[i].x = radius * cosf(valueVerts * i); 
	  verts[i].y = radius * sinf(valueVerts * i); 
    verts[i].r = R;
    verts[i].g = G;
    verts[i].b = B;
    verts[i].a = A;
	}
	
  glPushMatrix();
	glTranslatef(body->position.x, body->position.y, 0.0f);	

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLE_FAN);
	for(int i = 0; i <= countVerts; i++)
	{
    glColor4fv(&verts[i].r);
    glVertex2fv(&verts[i].x);
	}
	glEnd();
	glDisable(GL_BLEND);
		
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= countVerts; i++)
	{
    glColor4fv(&verts[i].r);
    glVertex2fv(&verts[i].x);
	}
	glEnd();
	
  const vertex line[2] = {
    {0.0f, 0.0f, 0.6f, 0.6f, 0.6f, A},
    {radius * cosf(body->orientation), radius * sinf(body->orientation), 0.6f, 0.6f, 0.6f, A}
  };

  glBegin(GL_LINES);
  for(int i = 0; i < 2; i++)
  {
    glColor4fv(&line[i].r);
    glVertex2fv(&line[i].x);
  }
  glEnd();
	
	glPopMatrix();
}


void DrawOBB(const Shape* shape)
{
  const real R = 0.4f, G = 0.4f, B = 0.4f, A = 0.4f;
	
  const RigidBody* body = shape->body;

	const Vec2 width = shape->width;
  
	glPushMatrix();

  glTranslatef(body->position.x, body->position.y, 0.0f);

	Mat2 Rot(body->orientation);
	
  Vec2 p1 = Rot * width * 0.5f;
	Vec2 p2 = Rot * Vec2(width.x, -width.y) * 0.5f;	
		
  const vertex verts[4] = 
  {
    { p1.x,  p1.y, R, G, B, A},
    { p2.x,  p2.y, R, G, B, A},
    {-p1.x, -p1.y, R, G, B, A},
    {-p2.x, -p2.y, R, G, B, A}
  };

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLE_FAN);
  for(int i = 0; i < 4; i++)
  {
    glColor4fv(&verts[i].r);
    glVertex2fv(&verts[i].x);
  }
	glEnd();
	glDisable(GL_BLEND);
		
	glBegin(GL_LINE_LOOP);
  for(int i = 0; i < 4; i++)
  {
    glColor4fv(&verts[i].r);
    glVertex2fv(&verts[i].x);
  }
	glEnd();

	glPopMatrix();
}


void DrawLine(const Vec2& p1, const Vec2& p2)
{
  const real R = 1.0f, G = 0.0f, B = 0.0f, A = 1.0f;

  const vertex verts[2] = 
  {
    {p1.x, p1.y, R, G, B, A},
    {p2.x, p2.y, R, G, B, A}
  };

  glBegin(GL_LINES);
  for(int i = 0; i < 2; i++)
  {
    glColor4fv(&verts[i].r);
    glVertex2fv(&verts[i].x);
  }
  glEnd();
}


void DrawPoint(const Vec2& p, const real& size)
{
  const real R = 1.0f, G = 0.0f, B = 0.0f, A = 1.0f;

  const vertex vert = { p.x, p.y, R, G, B, A };

  glPointSize(size);	
  glBegin(GL_POINTS);
  glColor4fv(&vert.r);
  glVertex2fv(&vert.x);
  glEnd();
}


void DrawShape(const Shape* shape)
{
	switch (shape->type)
	{
		case circle: DrawCircle(shape); break;

		case obb: DrawOBB(shape); break;
	}
}