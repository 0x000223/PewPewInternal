#pragma once

class Entity
{
public:
	union
	{
		DEFINE_MEMBER_N(bool, isDormant, offsets::m_bDormant);
		
		DEFINE_MEMBER_N(int, iHealth, offsets::m_iHealth);
		
		DEFINE_MEMBER_N(Vector3, vecOrigin, offsets::m_vecOrigin);
		
		DEFINE_MEMBER_N(int, iTeamNum, offsets::m_iTeamNum);

		DEFINE_MEMBER_N(int, boneMatrix, offsets::m_dwBoneMatrix);
		
		DEFINE_MEMBER_N(int, ArmorValue, offsets::m_ArmorValue);

		DEFINE_MEMBER_N(Vector3, aimPunchAngle, offsets::m_aimPunchAngle);

		DEFINE_MEMBER_N(float, angEyeAnglesX, offsets::m_angEyeAnglesX);
		
		DEFINE_MEMBER_N(float, angEyeAnglesY, offsets::m_angEyeAnglesY);

		DEFINE_MEMBER_N(Vector3, vecVelocity, offsets::m_vecVelocity);

		DEFINE_MEMBER_N(bool, bHasHelmet, offsets::m_bHasHelmet);
	};
};