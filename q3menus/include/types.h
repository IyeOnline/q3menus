#pragma once

#include <string>
#include <cassert>
#include <vector>
#include <array>
#include <algorithm>

#include "conversion.h"
#include "stringmanip.h"

namespace q3menus
{
	using cRX = const std::regex;//const regex
	using cRXr = const std::regex &; //const regex ref
	using cS = const std::string; //const string
	using cSr = const std::string &; //const string ref

	class rectType
	{
		public:
			std::array<int, 2> Pos = {{ 0 }};
			std::array<int, 2> Size = {{ 0 }};
			
		public:
			const int get_X() const { return Pos[0]; }
			const int get_Y() const { return Pos[1]; }
			const int get_Xsize() const { return Size[0]; }
			const int get_Ysize() const { return Size[1]; }
			
			void set_X(int i){ Pos[0] = i; }
			void set_Y(int i){ Pos[1] = i; }
			void set_Xsize(int i){ Size[0] = i; }
			void set_Ysize(int i){ Size[1] = i; }
			
			void set_Pos(int x,int y){ Pos[0] = x; Pos[1] = y; }
			template<typename T>
			void set_Pos(T a){Pos = a;}
			
			void set_Size(int x,int y){ Size[0] = x; Size[1] = y; }
			template<typename T>
			void set_Size(T a){Size = a;}
			
			void move( const int xadd, const int yadd){ Pos[0] += xadd; Pos[1] += yadd; }
			template<typename T>
			void move( T a ){ assert(a.size()==2); Pos[0] += a[0]; Pos[1] += a[1]; }

			const std::string getrectstring() const
			{
				return "rect " + std::to_string(Pos[0]) + " " + std::to_string(Pos[1]) + " " + std::to_string(Size[0]) + " " + std::to_string(Size[1]);
			}
			
			rectType() = default;
			
			rectType(int xin, int yin, int xsin, int ysin)
			{
				Pos[0] = xin;
				Pos[1] = yin;
				Size[0] = xsin;
				Size[1] = ysin;
			}
			
			template<typename T>
			rectType(T a)
			{
				Pos[0] = a[0];
				Pos[1] = a[1];
				Size[0] = a[2];
				Size[1] = a[3];
			}
			
			~rectType() = default;
	};



	class color
	{
		public:
			std::array<double,4> full = {{ 0 , 0 , 0 , 0 }};
			bool isEmpty = true;
			
		public:
			const std::string getcolorstring() const
			{
				std::stringstream ss;
				ss << full[0] << " " << full[1] << " " << full[2] << " " << full[3];
				return ss.str();//std::to_string(full[0]) + " " + std::to_string(full[1]) + " " + std::to_string(full[2]) + " " + std::to_string(full[3]);
			}
			
			color() = default;
			
			color(const double r_in, const double g_in, const double b_in, const double a_in)
			{
				full[0] = r_in;
				full[1] = g_in;
				full[2] = b_in;
				full[3] = a_in;
				isEmpty = false;
			};
			
			color(const std::array<double,4>& a)
			: full(a) , isEmpty(false)
			{};
			
			color(const std::vector<double>& a)
			: isEmpty(false)
			{ 
			  assert(a.size()==4);
			  full[0] = a[0];
			  full[1] = a[1];
			  full[2] = a[2];
			  full[3] = a[3];
			};
			
			
			~color(void){};
			
			void set_RGBA(double r,double g,double b,double a)
			{
				full[0] = r;
				full[1] = g;
				full[2] = b;
				full[3] = a;
				isEmpty = false;
			}
			
			friend std::ostream& operator<<(std::ostream& os, const color& c) 
			{
				os << c.full[0] << " " << c.full[1] << " " << c.full[2] << " " << c.full[3];
				return os;
			}

			
	};
}

// kate: space-indent off; replace-tabs off
