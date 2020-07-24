#include "pch.h"
#include "Transform.h"

namespace nc {
	std::istream& operator >> (std::istream stream, Transform& transform)
	{
		stream >> transform.position;
		stream >> transform.scale;
		stream >> transform.angle;

		return stream;
	}
	void Transform::Update(){
		nc::Matrix33 mxs;
		mxs.Scale(scale);
		
		nc::Matrix33 mxr;
		mxr.Rotate(angle);
		
		nc::Matrix33 mxt;
		mxt.Translate(position);

		matrix = mxs * mxr * mxt;
	}
}

