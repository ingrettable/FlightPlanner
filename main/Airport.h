#pragma once
#include <string>
using namespace std;
#include <math.h>

class Airport {
private:
	wstring code;
	int latitudeDegrees;
	int latitudeMinutes;
	int longitudeDegrees;
	int longitudeMinutes;

public :
	Airport(wstring initCode, 
			int initLatitudeDegrees,
			int initLatitudeMinutes,
			int initLongitudeDegrees,
			int initLongitudeMinutes) {
		this->code = initCode;
		this->latitudeDegrees = initLatitudeDegrees;
		this->latitudeMinutes = initLatitudeMinutes;
		this->longitudeDegrees = initLongitudeDegrees;
		this->longitudeMinutes = initLongitudeMinutes;
	}

	wstring getCode() {
		return this->code;
	}

	int getLatitudeDegrees() {
		return this->latitudeDegrees;
	}

	int getLatitudeMinutes() {
		return this->latitudeMinutes;
	}

	int getLongitudeDegrees() {
		return this->longitudeDegrees;
	}

	int getLongitudeMinutes() {
		return this->longitudeMinutes;
	}

	static float calculateDistance(Airport *a1, Airport *a2) {
		// CONSTANTS USED FOR DISTANCE CALCULATION
		float PI_F = 3.14159265358979f;
		float RADIAN_FACTOR = 180.0f / PI_F;
		float EARTH_RADIUS = 3963.0f;

		float lat1 = (float)a1->latitudeDegrees + (float)a1->latitudeMinutes / 60.0f;
		lat1 = lat1 / RADIAN_FACTOR;
		float long1 = -(float)a1->longitudeDegrees + (float)a1->longitudeMinutes / 60.0f;
		long1 = long1 / RADIAN_FACTOR;
		float lat2 = (float)a2->latitudeDegrees + (float)a2->latitudeMinutes / 60.0f;
		lat2 = lat2 / RADIAN_FACTOR;
		float long2 = -(float)a2->longitudeDegrees + (float)a2->longitudeMinutes / 60.0f;
		long2 = long2 / RADIAN_FACTOR;

		float x = (float)(
			(std::sin(lat1) * std::sin(lat2))
			+ (std::cos(lat1)
				* std::cos(lat2)
				* std::cos(long2 - long1))
			);
		float x2 = (float)(std::sqrt(1.0f - (x * x)) / x);
		float distance = (float)(EARTH_RADIUS * std::atan(x2));
		return distance;
	}
};