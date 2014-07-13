
#ifndef	_RENDERING_HH_
#define	_RENDERING_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>
#include	"Game.hh"
#include	"Interface.hh"

class Rendering
{
	public:
		MD2Obj  modelList[21];

		Rendering();
		~Rendering();
		bool LoadTexture(char *TexName, GLuint TexHandle);
		void loadObj(MD2Obj &object, char *pathMod, char *pathText);
		void  drawObject(MD2Obj &model, float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz, int &CurFrame);
		void  drawList(MD2Obj *, int &, std::vector<square> &, std::vector<player> &, int, int);
		void  Render(int fd, Game &parser);
		void  movePlayer(int);
};

#endif