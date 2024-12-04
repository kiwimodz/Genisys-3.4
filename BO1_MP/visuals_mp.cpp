#include<Includes.h>


#pragma region visual handles

void set_bound(int index) { bot.esp.bound = index; }
void set_snap(int index) { bot.esp.snaplines = index; }
String bound_type[6] = { "None", "Border", "Corner", "Border filled", "3D box", "3D triangle" };

String bound_typedec[6] = { "No option selected", "Draw border rect", "Draw corner rect", "Draw rect filled", "Draw 3D box", "Draw 3D triangle" };

String snap_type[4] = { "None", "Top", "Middle", "Bottom" };

String snap_typedec[4] = { "No option selected", "Top", "Middle", "Bottom" };

void set_mod(int index) {
	switch (index) {
	case 0:
		bot.esp.modm = MOD_PISTOL_BULLET;
		break;
	case 1: bot.esp.modm = MOD_RIFLE_BULLET;
		break;
	case 2:  bot.esp.modm = MOD_HEAD_SHOT;
		break;
	default:
		bot.esp.modm = MOD_PISTOL_BULLET;
		break;
	}
}
void set_pen(int index) {
	switch (index) {
	case 0:
		bot.esp.penm = PENETRATE_TYPE_SMALL;
		break;
	case 1: bot.esp.penm = PENETRATE_TYPE_MEDIUM;
		break;
	case 2:  bot.esp.penm = PENETRATE_TYPE_LARGE;
		break;
	default:
		bot.esp.penm = PENETRATE_TYPE_SMALL;
		break;
	}
}
void draw_bones(bool* rs) { bot.esp.bbones = !bot.esp.bbones; }
void draw_vangles(bool* rs) { bot.esp.bvangles = !bot.esp.bvangles; }
void draw_myvangles(bool* rs) { bot.esp.myvangles = !bot.esp.myvangles; }
void draw_compass(bool* rs) { bot.esp.bcompass = !bot.esp.bcompass; }
void draw_radartype(bool* rs) { bot.esp.bradartype = !bot.esp.bradartype; }
void draw_healthbar(bool* rs) { bot.esp.bhealthbar = !bot.esp.bhealthbar; }
void draw_tracers(bool* rs) { bot.esp.btracers = !bot.esp.btracers; }
void draw_clienthealth(bool* rs) { bot.esp.clienthealth = !bot.esp.clienthealth; }
void draw_proxwarn(bool* rs) { bot.esp.bprox = !bot.esp.bprox; }
void draw_crossh(bool* rs) { bot.esp.bdynamic = !bot.esp.bdynamic; }
void draw_names(bool* rs) { bot.esp.bnames = !bot.esp.bnames; }
void draw_dist(bool* rs) { bot.esp.bdist = !bot.esp.bdist; }
void draw_chams(bool* rs) { bot.esp.bchams = !bot.esp.bchams; }
void draw_wall(bool* rs) { bot.esp.bwall = !bot.esp.bwall; }
void draw_ewall(bool* rs) { bot.esp.ebwall = !bot.esp.ebwall; }

void draw_weapsworld(bool* rs) { bot.esp.bweapsworld = !bot.esp.bweapsworld; }
void draw_radartracers(bool* rs) { bot.esp.bradartracers = !bot.esp.bradartracers; }
void draw_nadesworld(bool* rs) { bot.esp.bnadesworld = !bot.esp.bnadesworld; }
void draw_scavsworld(bool* rs) { bot.esp.bpickupscavsworld = !bot.esp.bpickupscavsworld; }
void draw_weappickupidsworld(bool* rs) { bot.esp.bpickupweaponsworld = !bot.esp.bpickupweaponsworld; }
void draw_weappickupidsradar(bool* rs) { bot.esp.bradrpickupweaps = !bot.esp.bradrpickupweaps; }
void draw_draw_scavsradar(bool* rs) { bot.esp.bradrpickupscavs = !bot.esp.bradrpickupscavs; }
void draw_hellisradar(bool* rs) { bot.esp.bradrhelis = !bot.esp.bradrhelis; }
void draw_doggosradar(bool* rs) { bot.esp.bradrdogos = !bot.esp.bradrdogos; }
void draw_vehiclesradar(bool* rs) { bot.esp.bradrvehicles = !bot.esp.bradrvehicles; }
void draw_turretsradar(bool* rs) { bot.esp.bradrturrets = !bot.esp.bradrturrets; }
void draw_artilleryradar(bool* rs) { bot.esp.bradrartillery = !bot.esp.bradrartillery; }
void draw_worldents(bool* rs) { bot.esp.benableworldents = !bot.esp.benableworldents; }
void draw_nadesradar(bool* rs) { bot.esp.bradrnades = !bot.esp.bradrnades; }
void draw_xhscavs(bool* rs) { bot.esp.bxhscavs = !bot.esp.bxhscavs; }
void draw_xhweaps(bool* rs) { bot.esp.bxhweapspickupids = !bot.esp.bxhweapspickupids; }
void draw_targetfinder(bool* rs) { bot.esp.btargetfinder = !bot.esp.btargetfinder; }
void draw_targetinfo(bool* rs) { bot.esp.btargetinfo = !bot.esp.btargetinfo; }

#pragma endregion

int CG_IsClientInOurParty_t[2] = { 0x714C8, TOC };
bool(*CG_IsClientInOurParty_f)(int localClientNum, int clientNum) = (bool(*)(int localClientNum, int clientNum))CG_IsClientInOurParty_t;

bool __cdecl CG_IsClientInOurParty(int localClientNum, int clientNum) {
	CG_IsClientInOurParty_f(localClientNum, clientNum);
}

int CG_DrawOverheadNames_t[2] = { 0x3ECD8, TOC };
void(*CG_DrawOverheadNames_f)(int localClientNum, centity_s* cent, float alpha, int mode) = (void(*)(int, centity_s*, float, int))CG_DrawOverheadNames_t;

void __cdecl CG_DrawOverheadNames(int localClientNum, centity_s* cent, float alpha, int mode) {
	if (!strstr(cg->clients[cent->ClientNumber].PlayerName, "^")) {
		CG_DrawOverheadNames_f(localClientNum, cent, alpha, mode);
	}
}

bool Prox_in_Circle(Vector3 center, int radius, Vector3 Ent) {
	return (((center.x - Ent.x) * (center.x - Ent.x)) + ((center.y - Ent.y) * (center.y - Ent.y)) < (radius * radius));//is enermy near
}

Vector3 AnglesToForward(Vector3 startO, Vector3 Angles, float scale) {
	Vector3 forwardedAngle;
	AngleVectors_(Angles, &forwardedAngle, 0, 0);
	return (startO + (forwardedAngle * scale));
}

int R_AddCmdDrawStretchPicRotateXYInternal_t[2] = { 0x76A444, TOC };
void(*R_AddCmdDrawStretchPicRotateXYInternal_f)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float angle, float* Color, pvoid material) = (void(*)(float, float, float, float, float, float, float, float, float, float*, pvoid))R_AddCmdDrawStretchPicRotateXYInternal_t;

void R_AddCmdDrawStretchPicRotateXYInternal(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float angle, color c) {
	R_AddCmdDrawStretchPicRotateXYInternal_f(x, (dc.height > 720) ? y * (1.5) : y, w, (dc.height > 720) ? h * (1.5) : h, s0, t0, s1, t1, angle, (float*)&c, white);
}

int R_GetCommandBuffer_a[2] = { 0x0769f6c, TOC };
int (*R_GetCommandBuffer)(int renderCmd, int bytes) = (decltype(R_GetCommandBuffer))R_GetCommandBuffer_a;

int R_ConvertColorToBytes_a[2] = { 0x794980, TOC };
void(*R_ConvertColorToBytes)(float* colorFloat, int* colorBytes) = (decltype(R_ConvertColorToBytes))R_ConvertColorToBytes_a;

struct GfxPointVertex {
	Vector3 xyz;
	GfxColor color;
};

struct GfxCmdDrawLines {
	GfxCmdHeader header;
	__int16 lineCount;
	char width;
	char dimensions;
	GfxPointVertex verts[2];
};

void DrawLine(float x1, float y1, float x2, float y2, color col, float thickness = 1) {
	auto draw_line_command = (GfxCmdDrawLines*)R_GetCommandBuffer(21, (sizeof(GfxCmdDrawLines) * 2));
	if (draw_line_command != NULL) {
		int col1;
		R_ConvertColorToBytes((float*)&col, &col1);
		R_ConvertColorToBytes((float*)&col, &col1);

		GfxPointVertex verts[2];

		verts[0].xyz = { x1, y1, 0 };
		verts[0].color.packed = col1;

		verts[1].xyz = { x2, y2, 0 };
		verts[1].color.packed = col1;

		draw_line_command->dimensions = 2;
		draw_line_command->width = thickness;
		draw_line_command->lineCount = 1;
		_sys_memcpy(&draw_line_command->verts, &verts, sizeof(GfxPointVertex) * 2);
	}
}

void DrawWorldLine(Vector3 Pos1, Vector3 Pos2, color LineColor, int LineWidth) {
	Vector2 ScreenProj[2];

	if (!WorldPosToScreenPos(Pos1, &ScreenProj[0]) || !WorldPosToScreenPos(Pos2, &ScreenProj[1]))
		return;

	DrawLine(ScreenProj[0].x, ScreenProj[0].y, ScreenProj[1].x, ScreenProj[1].y, LineColor, 1);
}

void DrawPolyLine(Vector3* Points, size_t szArr, color LineColor, int LineWidth) {

	for (int i = 0; i < szArr - 1; i++)
		DrawWorldLine(Points[i], Points[i + 1], LineColor, LineWidth);
}

class EntityTrails {
private:
	Vector3 TrailPoints[2047][50];
	int TrailTickHanlde[2047];

public:
	void MainHandler();
	void DrawTrail(int EntNumber, color Color, int LineWidth);
};

void EntityTrails::MainHandler() {
	if (!cg->serverTime)
		return;

	for (int i = 0; i < 2046; i++)
		if (!centity[i].State)
			for (int x = 0; x < 50; x++)
				this->TrailPoints[i][x] = Vector3(0, 0, 0);
}

void EntityTrails::DrawTrail(int EntNum, color TrailColor, int LineWidth) {
	size_t PointSize = 49;

	if (Sys_Milliseconds() - this->TrailTickHanlde[EntNum] > 30) {
		for (int i = 0; i < PointSize; i++)
			this->TrailPoints[EntNum][i] = this->TrailPoints[EntNum][i + 1];

		this->TrailPoints[EntNum][PointSize] = centity[EntNum].Origin;

		this->TrailTickHanlde[EntNum] = Sys_Milliseconds();
	}

	for (int i = 0; i < PointSize + 1; i++)
		if (this->TrailPoints[EntNum][i] == Vector3(0, 0, 0))
			this->TrailPoints[EntNum][i] = centity[EntNum].Origin;

	Vector3 Vel = centity[EntNum].Origin - centity[EntNum].OldOrigin;

	if (Vel.x || Vel.y || Vel.z)
		DrawPolyLine(this->TrailPoints[EntNum], PointSize + 1, TrailColor, LineWidth);
}

EntityTrails CIANiggers;

void DrawLineV(Vector2 From, Vector2 To, color col, int s) {
	DrawLine(From.x, From.y, To.x, To.y, col, s);
}

void MakeLines(Vector3 Origin, float X1, float Y1, float Z1, float X2, float Y2, float Z2, color colors, int size = 1) {
	Vector2 Screen1, Screen2;

	Vector3 Origin1(Origin.x + X1, Origin.y + Y1, (Origin.z + Z1) - 5);
	Vector3 Origin2(Origin.x + X2, Origin.y + Y2, (Origin.z + Z2) - 5);
	if (WorldPosToScreenPos(Origin1, &Screen1) && WorldPosToScreenPos(Origin2, &Screen2)) {
		DrawLineV(Screen1, Screen2, colors, 1);
	}
}

void DrawVAngles(Vector3 FromOrigin, int Entity, color ESP) {
	Vector2 Screen1, Screen2;
	float Scale = 400;
	Vector3 From(FromOrigin.x, FromOrigin.y, FromOrigin.z);
	Vector3 ToForward = AnglesToForward(From, cgst->clients[Entity].viewAngle, Scale);
	if (WorldPosToScreenPos(From, &Screen1)) {
		if (WorldPosToScreenPos(ToForward, &Screen2)) {
			DrawLineV(Screen1, Screen2, ESP, 1);
		}
	}
}

float DrawLineRotatedAroundPoint(float CenterX, float CenterY, float rX1, float rY1, float rX2, float rY2, float Rotation, color Color) {
	Vector2 Rot1;
	Vector2 Rot2;
	float Rad = Rotation / 180 * 3.14159265358979323846f;

	Rot1.x = rY1 * cosf(Rad) - rX1 * sinf(Rad);
	Rot1.y = rX1 * cosf(Rad) + rY1 * sinf(Rad);

	Rot2.x = rY2 * cosf(Rad) - rX2 * sinf(Rad);
	Rot2.y = rX2 * cosf(Rad) + rY2 * sinf(Rad);

	Vector2 Position1(CenterX + Rot1.x, CenterY + Rot1.y);
	Vector2 Position2(CenterX + Rot2.x, CenterY + Rot2.y);

	DrawLine(Position1.x, Position1.y, Position2.x, Position2.y, Color, bot.customt);
}

void DCrosshair(color ESP) {
	Vector2 Center = { cg->refdef.Width / 2, cg->refdef.Height / 2 };

	float_t Size = 0;

	if (bot.customrs != 0.0f) {
		if (bot.customrs > 0.0f) {
			if (bot.customr < 180.0f) {
				bot.customr += bot.customrs;
			} else {
				bot.customr = 0.0f;
			}
		}
	}

	if (bot.customxhd) {
		Size = cg->spreadMultiplier / 5;
	}

	if (!bot.customxh) {
		DrawLine(Center.x - 15, Center.y + 15, Center.x - 4 - Size / 2, Center.y + 4, ESP, 1);//Bottom left to center
		DrawLine(Center.x + 15, Center.y + 15, Center.x + 4 + Size / 2, Center.y + 4, ESP, 1);// Bottom right to center
		DrawLine(Center.x + 15, Center.y - 15, Center.x + 4 + Size / 2, Center.y - 4, ESP, 1);//Top right to center
		DrawLine(Center.x - 15, Center.y - 15, Center.x - 4 - Size / 2, Center.y - 4, ESP, 1);//Top left to center
	}

	else if (bot.nazixh) {
		static float Rotation = 0.0f;
		Rotation++;

		DrawLineRotatedAroundPoint(Center.x, Center.y, -100.0f, 0.0f, 100.0f, 0.0f, Rotation, ESP); //Horizontal line
		DrawLineRotatedAroundPoint(Center.x, Center.y, 0.0f, -100.0f, 0.0f, 100.0f, Rotation, ESP); //Vertical line

		DrawLineRotatedAroundPoint(Center.x, Center.y, -100.0f, 0.0f, -100.0f, -100.0f, Rotation, ESP); //Left thingy
		DrawLineRotatedAroundPoint(Center.x, Center.y, 0.0f, -100.0f, 100.0f, -100.0f, Rotation, ESP); //Top Thingy
		DrawLineRotatedAroundPoint(Center.x, Center.y, 100.0f, 0.0f, 100.0f, 100.0f, Rotation, ESP); //Right Thingy
		DrawLineRotatedAroundPoint(Center.x, Center.y, 0.0f, 100.0f, -100.0f, 100.0f, Rotation, ESP); //Bottom Thingy
	}

	else {
		DrawLineRotatedAroundPoint(Center.x, Center.y, -bot.customx - Size / 2, +bot.customy + Size / 2, -bot.customw - Size / 2, +bot.customh + Size / 2, bot.customr, ESP);//Bottom left to center
		DrawLineRotatedAroundPoint(Center.x, Center.y, +bot.customx + Size / 2, +bot.customy + Size / 2, +bot.customw + Size / 2, +bot.customh + Size / 2, bot.customr, ESP);// Bottom right to center
		DrawLineRotatedAroundPoint(Center.x, Center.y, +bot.customx + Size / 2, -bot.customy - Size / 2, +bot.customw + Size / 2, -bot.customh - Size / 2, bot.customr, ESP);//Top right to center
		DrawLineRotatedAroundPoint(Center.x, Center.y, -bot.customx - Size / 2, -bot.customy - Size / 2, -bot.customw - Size / 2, -bot.customh - Size / 2, bot.customr, ESP);//Top left to center
	}
}

void HealthBar(cg_s* cgss) {
	/// Healthbar Variables
	color hcolor = cgss->health >= 80 ? color(0, 255, 0, 255) : ((cgss->health >= 50 && cgss->health < 80) ? color(255, 255, 0, 255) : color(255, 0, 0, 255));
	float_t Width = 200, Height = 15, X = cgss->refdef.Width / 2, Y = cgss->refdef.Height - 27;
	float_t wFactor = (Width / 100), wScale = cgss->health * wFactor;
	/// Draw Healthbar
	DrawShaderEsp1(X - Width / 2, Y, Width, Height, 0, color(0, 0, 0, 100), white, align_left);
	DrawShaderEsp1(X - Width / 2 + 1, Y + 1, cgss->health > cg->maxHealth ? wScale = 100 * wFactor - 2 : wScale - 2, Height - 2, 0, hcolor, white, align_left);
	char boolBuff[100];
	Com_Sprintf(boolBuff, sizeof(boolBuff), "Health %i/100", cgss->health);
	DrawTextWithEffectsUI(boolBuff, X, (dc.height > 720) ? Y - 530 : Y + (dc.height / 1.41) + 22, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), align_center);
}

void DrawOutline(float x, float y, float width, float height, color color, const char* material, int thickness) {
	DrawShaderEsp(x - thickness, y - thickness, width + (thickness * 2), thickness, 0, color, white, align_left); // Top
	DrawShaderEsp(x - thickness, y + height, width + (thickness * 2), thickness, 0, color, white, align_left); // Bottom
	DrawShaderEsp(x - thickness, y - thickness, thickness, height + thickness, 0, color, white, align_left); // Left
	DrawShaderEsp(x + width, y - thickness, thickness, height + (thickness * 2), 0, color, white, align_left); // Right
}

void DrawBorderBox(Vector2 HeadPosition, Vector2 FootPosition, color BoxColor) {
	float BoxHeight = (FootPosition.y - HeadPosition.y), BoxWidth = (dc.height > 720) ? BoxHeight / 2.5 : BoxHeight / 1.8;
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight - 1), BoxWidth, 3, 0, color(0, 0, 0, 255), white, align_left);//top
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), FootPosition.y - 1, BoxWidth + 2, 3, 0, color(0, 0, 0, 255), white, align_left);//bot
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight, 0, color(0, 0, 0, 255), white, align_left);//left
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight + 3, 0, color(0, 0, 0, 255), white, align_left);//right
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), BoxWidth, 1, 0, BoxColor, white, align_left);//top
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), FootPosition.y, BoxWidth + 1, 1, 0, BoxColor, white, align_left);
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, white, align_left);
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, white, align_left);
}

void DrawPLayerHealth(Vector2 HeadPosition, Vector2 FootPosition, color BoxColor) {
	float BoxHeight = (FootPosition.y - HeadPosition.y), BoxWidth = (dc.height > 720) ? BoxHeight / 2.5 : BoxHeight / 1.8;
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) + 10), (FootPosition.y - BoxHeight - 1), BoxWidth, 3, 0, color(0, 0, 0, 255), white, align_left);//top
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), FootPosition.y - 1, BoxWidth + 2, 3, 0, color(0, 0, 0, 255), white, align_left);//bot
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight, 0, color(0, 0, 0, 255), white, align_left);//left
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight + 3, 0, color(0, 0, 0, 255), white, align_left);//right
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), BoxWidth, 1, 0, BoxColor, white, align_left);//top
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), FootPosition.y, BoxWidth + 1, 1, 0, BoxColor, white, align_left);
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, white, align_left);
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, white, align_left);
}


float GetBoxWidth(int client) {
	if (centity[client].Flags & STANCE_PRONE)
		return 35;
	else return 17;
}

float GetBoxHeight(int client) {
	if (centity[client].Flags & STANCE_PRONE)
		return 25;
	else if (centity[client].Flags & STANCE_CROUCH)
		return 55;
	else return 70;
}

void RotatePoint(Vector3 point, Vector3 center, float yaw, Vector3 out) {
	float flAngleCos = Cos(((-yaw + 180.0f) / 360.0f - 0.25f) * (M_PI * 2)),
		flAngleSin = Sin(((-yaw + 180.0f) / 360.0f - 0.25f) * (M_PI * 2)),
		flDifferenceX = point.x - center.x,
		flDifferenceY = point.y - center.y;

	out.x = center.x + flAngleSin * flDifferenceX - flAngleCos * flDifferenceY;
	out.y = center.y + flAngleCos * flDifferenceX + flAngleSin * flDifferenceY;
	out.z = point.z;
}

void Draw3DTriBox(int client, color sColor) {
	Vector3 Center = centity[client].Origin;
	Center.z += 5;
	float W = GetBoxWidth(client), H = GetBoxHeight(client);
	W *= 1.5;
	H *= 1.2;
	//bottom
	MakeLines(Center, -W, -W, 0, W, -W, 0, sColor, 1);
	MakeLines(Center, -W, -W, 0, -W, W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, W, -W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, -W, W, 0, sColor, 1);
	//middle
	MakeLines(Center, -W, -W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, -W, W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, W, -W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, W, W, 0, 0, 0, H, sColor, 1);
}

void Draw3DBox(int client, color scolor) {
	Vector3 Center = centity[client].Origin;

	float W = GetBoxWidth(client), H = GetBoxHeight(client);

	MakeLines(Center, -W, W, 0, W, W, 0, scolor);
	MakeLines(Center, -W, W, 0, -W, W, H, scolor);
	MakeLines(Center, W, W, 0, W, W, H, scolor);
	MakeLines(Center, -W, W, H, W, W, H, scolor);

	MakeLines(Center, -W, W, 0, -W, -W, 0, scolor);
	MakeLines(Center, W, -W, 0, W, W, 0, scolor);
	MakeLines(Center, W, -W, 0, -W, -W, 0, scolor);
	MakeLines(Center, -W, -W, 0, -W, -W, H, scolor);

	MakeLines(Center, W, -W, 0, W, -W, H, scolor);
	MakeLines(Center, -W, W, H, -W, -W, H, scolor);
	MakeLines(Center, W, -W, H, W, W, H, scolor);
	MakeLines(Center, W, -W, H, -W, -W, H, scolor);
}

void DrawBorderBox(int client, Vector2 HeadPosition, Vector2 FootPosition, color Boxcolor) {
	float BoxHeight = (FootPosition.y - HeadPosition.y);
	float BoxWidth;

	if (centity[client].Flags & STANCE_PRONE)
		BoxWidth = BoxHeight / 0.9;
	else
		BoxWidth = BoxHeight / 1.8;

	DrawShaderEsp((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), BoxWidth, 1, 0, Boxcolor, white, align_left);
	DrawShaderEsp((FootPosition.x - (BoxWidth / 2)), FootPosition.y, BoxWidth, 1, 0, Boxcolor, white, align_left);
	DrawShaderEsp((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, Boxcolor, white, align_left);
	DrawShaderEsp((FootPosition.x + (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, Boxcolor, white, align_left);
}

void DrawBoxSolid(int client, Vector2 HeadPosition, Vector2 FootPosition, color BoxColor) {
	float BoxHeight;
	float BoxWidth;
	BoxColor.a = 0.60f;
	BoxHeight = (FootPosition.y - HeadPosition.y), BoxWidth = (dc.height > 720) ? BoxHeight / 2.5 : BoxHeight / 1.8;

	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), FootPosition.y - BoxHeight, BoxWidth - 1, BoxHeight - 1, 0, BoxColor, frame_color_debug, align_left);//filled
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight - 1), BoxWidth, 3, 0, color(0, 0, 0, 255), white, align_left);//top
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), FootPosition.y - 1, BoxWidth + 2, 3, 0, color(0, 0, 0, 255), white, align_left);//bot
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight, 0, color(0, 0, 0, 255), white, align_left);//left
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight + 3, 0, color(0, 0, 0, 255), white, align_left);//right
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), BoxWidth, 1, 0, BoxColor, white, align_left);//top
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), FootPosition.y, BoxWidth + 1, 1, 0, BoxColor, white, align_left);
	DrawShaderEsp1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, white, align_left);
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, white, align_left);
}

void DrawCorneredBox(int client, Vector2 head, Vector2 foot, color color) {
	float BoxHeight;
	float BoxWidth;
	BoxHeight = (foot.y - head.y), BoxWidth = (dc.height > 720) ? BoxHeight / 2.5 : BoxHeight / 1.8;

	int WidthThird = BoxWidth / 4;
	int HeightThird = WidthThird;

	DrawShaderEsp1(head.x - BoxWidth / 2, foot.y - BoxHeight - 1, WidthThird, 1, 0, color, white, align_left);//h
	DrawShaderEsp1(head.x - BoxWidth / 2, foot.y - BoxHeight - 1, 1, HeightThird, 0, color, white, align_left); //v
																								  //topright
	DrawShaderEsp1((head.x + BoxWidth / 2) - WidthThird, foot.y - BoxHeight - 1, WidthThird, 1, 0, color, white, align_left); //h
	DrawShaderEsp1(head.x + BoxWidth / 2, foot.y - BoxHeight - 1, 1, HeightThird, 0, color, white, align_left);//v
																								 //bottom left
	DrawShaderEsp1(head.x - BoxWidth / 2, foot.y - 3, WidthThird, 1, 0, color, white, align_left); //h
	DrawShaderEsp1(head.x - BoxWidth / 2, foot.y - HeightThird - 3, 1, HeightThird, 0, color, white, align_left);//v
																																 //bottom right
	DrawShaderEsp1((head.x + BoxWidth / 2) - WidthThird, foot.y - 3, WidthThird, 1, 0, color, white, align_left);//h
	DrawShaderEsp1(head.x + BoxWidth / 2, foot.y - HeightThird - 3, 1, HeightThird + 1, 0, color, white, align_left); //v		
}

void HandleESPBox(int Index, int client, Vector2 FeetPos, Vector2 HeadPos, color scolor) {
	if (bot.esp.bound == 0)
		null;
	if (bot.esp.bound == 1)
		DrawBorderBox(HeadPos, FeetPos, scolor);
	if (bot.esp.bound == 2)
		DrawCorneredBox(client, HeadPos, FeetPos, scolor);
	if (bot.esp.bound == 3)
		DrawBoxSolid(client, HeadPos, FeetPos, scolor);
	if (bot.esp.bound == 4)
		Draw3DBox(client, scolor);
	if (bot.esp.bound == 5)
		Draw3DTriBox(client, scolor);
}

void DrawBone(centity_s* Entity, short from, short to, color color) {
	Vector2 FromCoords, ToCoords;
	Vector3 fromv, tov;
	AimTarget_GetTagPos(Entity, from, &fromv);
	AimTarget_GetTagPos(Entity, to, &tov);
	if (WorldPosToScreenPos(fromv, &FromCoords) && WorldPosToScreenPos(tov, &ToCoords))
		DrawLine(FromCoords.x, FromCoords.y, ToCoords.x, ToCoords.y, color, 1);
}

#pragma region crosshair compass
Vector2 cCenter;

int CG_DrawWarningPointer_t[2] = { 0x39FA8, TOC };
void(*CG_DrawWarningPointer_f)(int client, float centerX, float centerY, Vector3* grenadeOffset, float* color, const float radiusOffset, const float scaleFactor) = (void(*)(int, float, float, Vector3*, float*, const float, const float))CG_DrawWarningPointer_t;

void  CG_DrawWarningPointer(int i, color c, const float radiusOffset, const float scaleFactor) {
	float centerX = cg->refdef.Width / 2;
	float centerY = cg->refdef.Height / 2;
	Vector3 grenadeOffset;
	grenadeOffset -= (centity[cg->clientNum].Origin - centity[i].Origin);
	CG_DrawWarningPointer_f(0, centerX, centerY, &grenadeOffset, (float*)&c, radiusOffset, scaleFactor);
}
#pragma endregion

void HandleSnapLines(int client, Vector2* FeetLocation, Vector2* HeadLocation, color sColor) {
	if (bot.esp.snaplines == 0) return;
	Vector2 start;
	Vector2 end;
	switch (bot.esp.snaplines) {
	case 1:
		//Top
		start.x = dc.width / 2; start.y = dc.height - dc.height + 15;
		end.x = HeadLocation->x; end.y = HeadLocation->y;
		DrawLineV(start, end, sColor, 1.2);
		break;
	case 2:
		//Middle
		start.x = dc.width / 2; start.y = dc.height / 2;
		end.x = FeetLocation->x, end.y = FeetLocation->y,
			DrawLineV(start, end, sColor, 1.2);
		break;
	case 3:
		//Bottom
		start.x = dc.width / 2; start.y = dc.height - 15;
		end.x = FeetLocation->x; end.y = FeetLocation->y;
		DrawLineV(start, end, sColor, 1.2);
		break;
	}
}

void prox(int i) {
	if (Prox_in_Circle(centity[cg->clientNum].Origin, 350.0, centity[i].Origin)) {
		DrawTextWithEffectsUI("[Enemy] is near", cg->refdef.Width / 2, 34, .95, color(255, 0, 0, 255), align_center);
	}
}

Vector2 RadarCenter_;
float RadarSize[2];
Vector2 Center_;

void EntityCount() {
	bot.esp.getNumberOfEntities = 0;
	bot.esp.maxclients = 0;

	if (cl_ingame_()) {
		for (int i = 0; i < 1048; i++) {
			if (!menu->ents) {

				if (centity[i].Type > 0) {
					if (((centity[i].State & (1 << 6)) != 0)) {
						bot.esp.getNumberOfEntities++;

					}
				}
			}

			if (((centity[i].State & (1 << 6)) != 0) && i != cg->clientNum) {
				if (centity[i].Type == ET_PLAYER && !cg->clients[i].Dead) {
					bot.esp.maxclients++;
				}
			}
		}
	} else {
		bot.esp.maxclients = 18;
	}
}

void EntityVisuals(int i) {
	if (bot.esp.benableworldents) {

		Vector2 Location;
		Vector2 ET_ItemPosition;
		Vector3 EntOrigin = centity[i].Origin;
		int wid = centity[i].WeaponID;
		int pid = centity[i].pickupId;

		WeaponVariantDef* weapondefid = BG_GetWeaponVariantDef(pid);
		if (!weapondefid)return;


		if (centity[i].Type > 0) {
			if (WorldPosToScreenPos(EntOrigin, &ET_ItemPosition)) {
				if (centity[i].Type == ET_ITEM) {
					if (((centity[i].State & (1 << 6)) != 0)) {
						if (!strcmp(weapondefid->name, "scavenger_item_mp") && bot.esp.bpickupscavsworld)//scavs
						{
							DrawShaderPP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), hud_scavenger_pickup, align_left);
						} else if (weapondefid->weapDef->hudIcon && bot.esp.bpickupweaponsworld)//weaps pick up
						{
							DrawShaderPP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
						}
					}
				}
				if (centity[i].Type == ET_MISSILE && bot.esp.bnadesworld)//nades
				{
					if (bot.esp.bnadetracers)
						CIANiggers.DrawTrail(i, menu->trcr, 2);

					if (((centity[i].State & (1 << 6)) != 0)) {
						if (weapondefid->weapDef->hudIcon) {
							DrawShaderPP(ET_ItemPosition.x - 40 / 2, ET_ItemPosition.y, 40, 40, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
						}
					}
				}
				if (centity[i].Type == ET_PLAYER && bot.esp.bweapsworld) {
					if (CScr_IsAlive(i)) {
						if (weapondefid->weapDef->hudIcon)//weapons
						{
							DrawShaderPP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
						} else {
							DrawShaderPP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), hint_mantle, align_left);
						}
					}
				}
			}
		}
	}
}

int CG_Vehicle_GetVehicleDef_t[2] = { 0xCBBF0, TOC };
VehicleDef* (*CG_Vehicle_GetVehicleDef_f)(centity_s* cent) = (VehicleDef * (*)(centity_s*))CG_Vehicle_GetVehicleDef_t;

VehicleDef* CG_Vehicle_GetVehicleDef(centity_s* cent) {
	return CG_Vehicle_GetVehicleDef_f(cent);
}

float _mm_xor_ps(float v15, float _mask__NegFloat_) {
	return v15 * _mask__NegFloat_;
}

int CG_CompassCalcDimensions_t[2] = { 0x2F810, TOC };
void(*CG_CompassCalcDimensions_f)(int compassType, cg_sa* cgaa, rectDef_s* parentRect, rectDef_s* rect, float* x, float* y, float* w, float* h) = (void(*)(int, cg_sa*, rectDef_s*, rectDef_s*, float*, float*, float*, float*))CG_CompassCalcDimensions_t;

void __cdecl CG_CompassCalcDimensions(int compassType, cg_sa* cgaa, rectDef_s* parentRect, rectDef_s* rect, float* x, float* y, float* w, float* h) {
	CG_CompassCalcDimensions_f(compassType, cgaa, parentRect, rect, x, y, w, h);
}

int R_AddCmdDrawStretchPicRotateSTInternal_t[2] = { 0x76A55C, TOC };
void(*R_AddCmdDrawStretchPicRotateSTInternal_f)(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float* color, void* material) = (void(*)(float, float, float, float, float, float, float, float, float, float, const float*, void*))R_AddCmdDrawStretchPicRotateSTInternal_t;

void __cdecl R_AddCmdDrawStretchPicRotateSTInternal(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float* color, void* material) {
	R_AddCmdDrawStretchPicRotateSTInternal_f(x, (dc.height > 720) ? y * (1.5 + menu->menusize) : y / (dc.aspect - menu->menusize), w, (dc.height > 720) ? h * (1.5 + menu->menusize) : h / (dc.aspect - menu->menusize), centerS, centerT, radiusST, scaleFinalS, scaleFinalT, angle, color, material);
}

void __cdecl R_AddCmdDrawStretchPicRotateSTInternal1(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float* color, void* material) {
	R_AddCmdDrawStretchPicRotateSTInternal_f(x, (dc.height > 720) ? y * (1.5 - menu->menusize) : y, w, (dc.height > 720) ? h * (1.5 - menu->menusize) : h, centerS, centerT, radiusST, scaleFinalS, scaleFinalT, angle, color, material);
}

int ScrPlace_ApplyRect_t[2] = { 0x15FFE0, TOC };
void(*ScrPlace_ApplyRect_f)(int r1, float* x, float* y, float* w, float* h, int horzAlign, int vertAlign) = (void(*)(int, float*, float*, float*, float*, int, int))ScrPlace_ApplyRect_t;

void __cdecl ScrPlace_ApplyRect(float* x, float* y, float* w, float* h, int horzAlign, int vertAlign) {
	ScrPlace_ApplyRect_f(0xFB9DE0, x, y, w, h, horzAlign, vertAlign);
}

void __cdecl CL_DrawStretchPicRotatedSTInternal(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, color c, pvoid Material) {
	ScrPlace_ApplyRect(&x, &y, &w, &h, horzAlign, vertAlign);
	R_AddCmdDrawStretchPicRotateSTInternal1(x, y, w, h, centerS, centerT, radiusST, scaleFinalS, scaleFinalT, angle, (float*)&c, Material);
}

void R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float Angle, float* colour, void* material) {
	int r31 = R_GetCommandBuffer(0xD, 0x34); //R_GetCommandBuffer
	if (r31) {
		if (!material)
			*(void**)(r31 + 0x4) = *(void**)0x2B3ABE8;
		else
			*(void**)(r31 + 0x4) = material;
		*(float*)(r31 + 0x8) = x;
		*(float*)(r31 + 0xC) = (dc.height > 720) ? y * 1.5 : y;
		*(float*)(r31 + 0x10) = w;
		*(float*)(r31 + 0x14) = (dc.height > 720) ? h * 1.5 : h;;
		*(float*)(r31 + 0x18) = centerS;
		*(float*)(r31 + 0x1C) = centerT;
		*(float*)(r31 + 0x20) = radiusST;
		*(float*)(r31 + 0x24) = scaleFinalS;
		*(float*)(r31 + 0x28) = scaleFinalT;
		int* r4 = (int*)(r31 + 0x2C);
		if (colour)
			R_ConvertColorToBytes(colour, r4); //R_ConvertColorToBytes
		else
			*r4 = -1;
		AngleNormalize360(Angle); //Normalize Angle
		*(float*)(r31 + 0x30) = Angle;
	}
}

float colour[] = { 1, 1, 1, 1 };

float rx, ry, rw, rh, cw, ch;

float Clampclamp(float i, float min, float max_) {

	if (i < min) {
		return min;
	}
	if (i > max_) {
		return max_;
	}
	return i;
}

enum CompassType {
	COMPASS_TYPE_PARTIAL = 0x0,
	COMPASS_TYPE_FULL = 0x1,
};

void __cdecl CG_CompassDrawPlayerMap_f() {
	Vector2 east, south, mapCenter;
	float delta, delta_4, texCenter, texCenter_4, texRadius, scaleFinalS, scaleFinalT, rotation;

	mapCenter.x = cg->refdef.ViewOrigin.x;
	mapCenter.y = cg->refdef.ViewOrigin.y;

	east.x = compass_data->compassNorth.y;
	east.y = _mm_xor_ps(compass_data->compassNorth.x, __mask_neg_float);
	south.x = _mm_xor_ps(compass_data->compassNorth.x, __mask_neg_float);
	south.y = _mm_xor_ps(compass_data->compassNorth.y, __mask_neg_float);

	delta = mapCenter.x - compass_data->compassMapUpperLeft.x;
	delta_4 = mapCenter.y - compass_data->compassMapUpperLeft.y;
	texCenter = (float)((float)(delta * east.x) + (float)(delta_4 * east.y)) / compass_data->compassMapWorldSize.x;
	texCenter_4 = (float)((float)(delta * south.x) + (float)(delta_4 * south.y)) / compass_data->compassMapWorldSize.y;

	if (compass_data->compassMapWorldSize.x <= compass_data->compassMapWorldSize.y) {
		texRadius = (float)(0.5 * compass_max_range) / compass_data->compassMapWorldSize.y;
		scaleFinalS = compass_data->compassMapWorldSize.y / compass_data->compassMapWorldSize.x;
		scaleFinalT = FLOAT_1_0;
	} else {
		texRadius = (float)(0.5 * compass_max_range) / compass_data->compassMapWorldSize.x;
		scaleFinalS = FLOAT_1_0;
		scaleFinalT = compass_data->compassMapWorldSize.x / compass_data->compassMapWorldSize.y;
	}

	rotation = _mm_xor_ps((cg->playerstate.viewAngles.y - compass_data->compassNorthYaw), __mask_neg_float);

	R_AddCmdDrawStretchPicRotateST(rx, ry, rw, rh, texCenter, texCenter_4, texRadius, scaleFinalS, scaleFinalT, rotation, colour, compass_data->compassMapMaterial);
}

int CG_WorldPosToCompass_a[2] = { 0x2F4D0, TOC };
bool  (*CG_WorldPosToCompass)(int compassType, cg_s* cgameGlob, rectDef_s* mapRect, Vector2* north, float* playerWorldPos, float* in, Vector2* out, Vector2* outClipped) = (decltype(CG_WorldPosToCompass))CG_WorldPosToCompass_a;

int YawVectors2D_a[2] = { 0x3CB050 , TOC };
void (*YawVectors2D)(float yaw, Vector2* out, int unk) = (decltype(YawVectors2D))YawVectors2D_a;

rectDef_s rect;

int Com_SessionMode_IsMode_t[2] = { Com_SessionMode_IsMode_a, TOC };
bool(*Com_SessionMode_IsMode_f)(eSessionModes_mode mode) = (bool(*)(eSessionModes_mode))Com_SessionMode_IsMode_t;

bool __cdecl Com_SessionMode_IsMode(eSessionModes_mode mode) {
	return Com_SessionMode_IsMode_f(mode);
}

void ToggleRadar() {

	*(uint32*)0x2E6EC4 = bot.esp.bradar ? 0x4E800020 : 0xF821FF31;
	*(uint32*)0x2E7108 = bot.esp.bradar ? 0x4E800020 : 0xF821FF11;
	*(uint32*)0x2E74A8 = bot.esp.bradar ? 0x4E800020 : 0xF821FF61;

	*(float*)0x2995934 = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x2995CDC = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x2995E14 = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x2996084 = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29961BC = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x299642C = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x299669C = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29ADF34 = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE06C = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE2DC = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE414 = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE54C = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE688 = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE7BC = bot.esp.bradar ? 0.0f : 1.0f;
	*(float*)0x29AE684 = bot.esp.bradar ? 0.0f : 1.0f;
}

void CG_CompassDrawPlayerMap() {
	if (bot.esp.bradar) {

		ch = (fabsf(Clampclamp(compass_max_range, 4000, 5000) - 6500) / 100) + rh / 110;
		cw = (fabsf(Clampclamp(compass_max_range, 4000, 5000) - 6500) / 100) + rw / 110;

		rh = bot.esp.scalewh;
		rw = bot.esp.scalewh;

		rx = 14;

		ry = 41;


		DrawShaderEsp(rx, ry, rw, rh, 0, color(0, 0, 0, 200), white, align_left);

		/*if (!zombiecheck())
		{*/
		ToggleRadar();
		CG_CompassDrawPlayerMap_f();
		//}
	} else {
		/*if (!zombiecheck())*/
		ToggleRadar();
	}
}

bool inks;
void DrawRadarOutLines(float x, float y, float width, float height, int thickness) {
	if (bot.esp.bradar) {
		R_AddCmdDrawStretchPicRotateST(x - thickness, y - thickness, width + (thickness * 2.1), thickness, 1, 1, 1, 1, 1, 180, (float*)&menu->skin6, gradient_fadein); // Top>
		R_AddCmdDrawStretchPicRotateST(x - thickness, y - thickness, width + (thickness * 2.1), thickness, 1, 1, 1, 1, 1, 0, (float*)&menu->skin4, gradient_fadein); // Top<
		R_AddCmdDrawStretchPicRotateST(x - thickness, y + height - 1, width + (thickness * 2.1), thickness, 1, 1, 1, 1, 1, 0, (float*)&menu->skin3, gradient_fadein); // Bottom>
		R_AddCmdDrawStretchPicRotateST(x - thickness, y + height - 1, width + (thickness * 2.1), thickness, 1, 1, 1, 1, 1, 180, (float*)&menu->skin5, gradient_fadein); // Bottom<
		R_AddCmdDrawStretchPicRotateST(x - thickness, y - thickness, thickness, height + thickness + 1 / 2, 1, 1, 1, 1, 1, -90, (float*)&menu->skin5, gradient_fadein); // Left>
		R_AddCmdDrawStretchPicRotateST(x - thickness, y - thickness, thickness, height + thickness + 1 / 2, 1, 1, 1, 1, 1, 90, (float*)&menu->skin6, gradient_fadein); // Left<
		R_AddCmdDrawStretchPicRotateST(x + width, y - thickness, thickness, height + (thickness * 2) - 2 / 2, 1, 1, 1, 1, 1, 90, (float*)&menu->skin4, gradient_fadein); // Right>
		R_AddCmdDrawStretchPicRotateST(x + width, y - thickness, thickness, height + (thickness * 2) - 2 / 2, 1, 1, 1, 1, 1, -90, (float*)&menu->skin3, gradient_fadein); // Right<

		DrawLine(x + width / 2, (dc.height > 720) ? ((y + (height / 2) * 1.5) + 10) : ((y + (height / 2))), x + cg->spreadMultiplier / 8, (dc.height > 720) ? y * 1.5 : y, color(255, 255, 255, 100), 1); // dynamic line right
		DrawLine(x + width / 2, (dc.height > 720) ? ((y + (height / 2) * 1.5) + 10) : ((y + (height / 2))), x + width - cg->spreadMultiplier / 8, (dc.height > 720) ? y * 1.5 : y, color(255, 255, 255, 100), 1); // dynamic line right

		DrawShaderEsp(x, y + height / 2, width, 2, 0, color(255, 255, 255, 100), white, align_left); // horz
		DrawShaderEsp(x + width / 2, y, 1, height, 0, color(255, 255, 255, 100), white, align_left); // vert

		if (dc.height > 720) {

			DrawShaderEsp(x + width / 2 - (cw) / 2, y + height / 2 - (ch) / 2, cw, ch + 5, 0, menu->skin3, compassping_player, align_left);
		}

		else {
			DrawShaderEsp(x + width / 2 - (cw) / 2, y + height / 2 - (ch) / 2, cw, ch + 5, 0, menu->skin3, compassping_player, align_left);
		}
	}
}

void DrawRadarDynamics(int i, color ESP, CompassType compasstype) {
	if (bot.esp.bradar) {
		rect.w = rw;
		rect.h = rh;

		rect.x = rx;
		rect.y = ry;

		Vector2 Out;
		Vector2 North;

		if (centity[i].Type > 0) {
			color finalcolor = CG_IsEntityFriendlyNotEnemy(&centity[i]) ? color(0, 255, 255, 255) : color(255, 0, 0, 255);

			YawVectors2D(cg->playerstate.viewAngles.y, &North, 0);

			CG_WorldPosToCompass(0, cg, &rect, &North, (float*)&cg->refdef.ViewOrigin, (float*)&centity[i].Origin, 0, &Out);

			Out.x += rect.w * 0.5 + rect.x;
			Out.y += rect.h * 0.5 + rect.y;

			if (((centity[i].State & (1 << 6)) != 0)) {
				if (bot.esp.bradrhelis) {

					if (centity[i].Type == ET_HELICOPTER) {
						VehicleDef* vd = CG_Vehicle_GetVehicleDef(&centity[i]);
						pvoid* mat = vd->compassIconMaterial;
						if (!strstr(*(char**)mat, "None") && mat != NULL) {
							DrawShaderP(Out.x - (cw + 30) / 2, Out.y - (ch + 30) / 2, cw + 30, ch + 30, cg->playerstate.viewAngles.y - centityt[i].pose.angles[1], finalcolor, mat, align_left);
						}
					}
				}

				if (bot.esp.bradrvehicles) {

					if (centity[i].Type == ET_VEHICLE) {
						VehicleDef* vd = CG_Vehicle_GetVehicleDef(&centity[i]);
						pvoid* mat = vd->compassIconMaterial;
						if (!strstr(*(char**)mat, "None") && mat != NULL) {
							DrawShaderP(Out.x - (cw + 10) / 2, Out.y - (ch + 10) / 2, cw + 10, ch + 10, (cg->playerstate.viewAngles.y - centityt[i].pose.angles[1]), finalcolor, mat, align_left);
						}
					}
				}

				if (bot.esp.bradrdogos) {
					if (centity[i].Type == ET_DOG) {
						DrawShaderP(Out.x - cw / 2, Out.y - ch / 2, cw, ch, 0, finalcolor, compassping_dog, align_left);
					}
				}

				if (bot.esp.bradrturrets) {

					if (centity[i].Type == ET_TURRET) {
						if (centityt[i].nextState.lerp.u.turret.flags > 101) {
							DrawShaderP(Out.x - (cw + 10) / 2, Out.y - (ch + 10) / 2, cw + 10, ch + 10, cg->playerstate.viewAngles.y - centityt[i].pose.angles[1], finalcolor, compass_sg_white, align_left);
						} else {
							Vector3 Turret_Angle = *(Vector3*)&centityt[i].nextState.lerp.u.turret.gunAngles;
							float Rotation = (cg->playerstate.viewAngles.y - (centityt[i].pose.angles[1]) - Turret_Angle.y);
							DrawShaderP(Out.x - (cw + 10) / 2, Out.y - (ch + 10) / 2, cw + 10, ch + 10, Rotation, finalcolor, compass_turret_white, align_left);
						}
					}
				}

				if (bot.esp.bradrartillery) {

					if (centity[i].Type == ET_MISSILE) {
						if (centityt[i].nextState.weapon == 143 || centityt[i].nextState.weapon == 144) {
							DrawShaderP(Out.x - (cw + 15) / 2, Out.y - (ch + 15) / 2, cw + 15, ch + 15, AngleNormalize360(cg->playerstate.viewAngles.y - centityt[i].pose.angles[1]), finalcolor, compass_hk, align_left);
						} else if (centityt[i].nextState.weapon == 148 || centityt[i].nextState.weapon == 149 || centityt[i].nextState.weapon == 150 || centityt[i].nextState.weapon == 146 || centityt[i].nextState.weapon == 145) {
							DrawShaderP(Out.x - (cw + 15) / 2, Out.y - (ch + 15) / 2, cw + 15, ch + 15, 0, finalcolor, waypoint_recon_artillery_strike, align_left);
						}
					}
				}

				if (bot.esp.bradrpickupscavs || bot.esp.bradrnades || bot.esp.bradrpickupweaps) {


					int wid = centity[i].WeaponID;
					int pid = centity[i].pickupId;

					WeaponVariantDef* weapondefid = BG_GetWeaponVariantDef(pid);

					if (!weapondefid)return;

					if (bot.esp.bradrpickupscavs) {

						if (!strcmp(weapondefid->name, "scavenger_item_mp")) {
							DrawShaderP(Out.x - cw / 2, Out.y - ch / 2, cw, ch, 0, color(255, 255, 255, 255), hud_scavenger_pickup, align_left);
						}
					}

					if (centity[i].Type == ET_ITEM) {
						if (bot.esp.bradrpickupweaps) {

							if (weapondefid->weapDef->hudIcon) {
								DrawShaderP(Out.x - (cw + 15) / 2, Out.y - ch / 2, cw + 15, ch, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
							}
						}
					}

					if (centity[i].Type == ET_MISSILE) {

						if (bot.esp.bradrnades) {

							if (weapondefid->weapDef->hudIcon)//nades
							{
								DrawShaderP(Out.x - cw / 2, Out.y - ch / 2, cw, ch, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
							}
						}
					}
				}
			}

			if (bot.esp.bplayers) {

				if (CScr_IsAlive(i) && i != cg->clientNum && centity[i].Type == ET_PLAYER) {
					DrawShaderEsp(Out.x - (cw / 2), Out.y - (ch / 2), cw, ch, (cg->playerstate.viewAngles.y - centityt[i].pose.angles[1]), ESP, compassping_player, align_left);
				}
			}

			if (bot.esp.bradartracers && local->alive) {

				if (i != cg->clientNum && i == local->target_num) {
					DrawLine(rx + rw / 2, (dc.height > 720) ? ((ry + (rh / 2) * 1.5) + 10) : ((ry + (rh / 2))), Out.x, (dc.height > 720) ? (Out.y * 1.5) : Out.y, menu->trcr, 1);
				}
			}
		}
	}
}

void DrawTargetScanner(float x, float y, float width, float height, color cross) {
	bool targetInBox = false;
	Vector2 screen;
	DrawStaticOutline1(x, y, width, height, menu->skin, 2.1);//border
	if (local->alive) {
		Vector3 tov;

		AimTarget_GetTagPos(&centity[local->target_num], bot.psztag[local->target_num], &tov);

		targetInBox = (WorldPosToScreenPos(tov, &screen)
			&& screen.x < x + width
			&& screen.x > x
			&& screen.y < y + height
			&& screen.y > y);

		if (targetInBox) {
			DrawLine(x, screen.y, screen.x, screen.y, cross, 2.1);
			DrawLine(screen.x, (y + height / 2) - (height / 2), screen.x, screen.y, cross, 2.1);
			DrawLine(screen.x, screen.y, (x + width / 2) + (width / 2), screen.y, cross, 2.1);
			DrawLine(screen.x, screen.y, screen.x, (y + height / 2) + (height / 2), cross, 2.1);
		}
	}
}

int SL_GetString_t[2] = { SL_GetString_a, TOC };
short(*SL_GetString_f)(const char* str, unsigned int user) = (short(*)(const char*, unsigned int))SL_GetString_t;

short SL_GetString(const char* str, unsigned int user) {
	return SL_GetString_f(str, user);
}

int PM_GetSprintLeft_t[2] = { 0x5C9EB8, TOC };
int(*PM_GetSprintLeft_f)(playerState_s* ps, const int gametime) = (decltype(PM_GetSprintLeft_f))PM_GetSprintLeft_t;

int BG_GetMaxSprintTime_t[2] = { 0x05C8318, TOC };
int(*BG_GetMaxSprintTime_f)(playerState_s* ps) = (decltype(BG_GetMaxSprintTime_f))BG_GetMaxSprintTime_t;

bool __cdecl PM_IsSprinting(playerState_s* ps) {
	int v1; // eax
	bool result; // al

	v1 = ps->sprintState.lastSprintStart;
	if (v1)
		result = v1 > ps->sprintState.lastSprintEnd;
	else
		result = 0;
	return result;
}

void Drawclientshealth(int i, Vector2 FootPosition, Vector2 HeadPosition) {
	float BoxHeight = (FootPosition.y - HeadPosition.y), BoxWidth = BoxHeight / 1.8;
	float_t Width = BoxHeight;
	float_t wScale = BoxHeight * ((float)gentity[i].health / (float)cg->maxHealth);
	color hcolor = color((255 - ((float)gentity[i].health * 2.55)), ((float)gentity[i].health * 2.55), 0.f, 255);
	DrawShaderEsp1((FootPosition.x + (BoxWidth / 2) - 1) + 3, FootPosition.y - (BoxHeight * ((float)gentity[i].health / 100)) - 1, 2, wScale + 2, 0, hcolor, white, align_left);
}

void draw_sprint_meter() {
	auto* ps = &cg->playerstate;
	auto sprint_time_max = static_cast<float>(BG_GetMaxSprintTime_f(ps));
	auto sprint_time_left = static_cast<float>(PM_GetSprintLeft_f(ps, cg->serverTime));
	color hcolor = color((255 - (static_cast<float>(sprint_time_left / 40) * 2.55)), ((static_cast<float>(sprint_time_left / 40)) * 2.55), 0.f, 255);
	DrawShaderEsp1(15, (((cg->refdef.Height / 2)) * 1.5) - 200, 8, 200, 0, color(0, 0, 0, 100), white, align_left);
	DrawShaderEsp1(15, (((cg->refdef.Height / 2)) * 1.5) - (200 * (sprint_time_left / sprint_time_max)), 8, (200 * (sprint_time_left / sprint_time_max)), 0, hcolor, white, align_left);
	DrawShaderEsp1(15, (((cg->refdef.Height / 2)) * 1.5) - (200 * ((Dvar_FindVar("player_sprintMinTime")->current.value * 1000) / sprint_time_max)), 8, 2, 0, color(255, 0, 0, 100), white, align_left);
}

Vector3 AnglesToForward_(Vector3* Angles, float Distance) {
	float angle, sp, sy, cp, cy, PiDiv;
	PiDiv = M_PI / 180.0f;
	angle = Angles->y * PiDiv;
	sy = sinf(angle);
	cy = cosf(angle);
	angle = Angles->x * PiDiv;
	sp = sinf(angle);
	cp = cosf(angle);
	Vector3 temp = Vector3(cp * cy * Distance, cp * sy * Distance, -sp * Distance);
	return temp;
}

struct CGrenadedata {
	int StartTime;
	int Delta;
	int EndTime;
	bool bRet;
};

CGrenadedata nade;
void DrawNadeFuseTimer(int i) {
	if (!bot.esp.benablenadefuse)return;

	if (cg->nextSnap->ps.grenadeTimeLeft != 0) {
		nade.StartTime = cg->nextSnap->ps.grenadeTimeLeft; nade.bRet = true;
		nade.Delta = cg->playerstate.commandTime;
		nade.EndTime = nade.StartTime;
	}

	int wid = centity[i].pickupId;
	WeaponVariantDef* weapondefid = BG_GetWeaponVariantDef(wid);
	Vector2 ET_ItemPosition;
	Vector3 EntOrigin = centity[i].Origin;

	if (WorldPosToScreenPos(EntOrigin, &ET_ItemPosition)) {
		if (centity[i].Type == ET_MISSILE) {
			if (((centity[i].State & (1 << 6)) != 0)) {
				if ((weapondefid->weapDef->hudIcon) && (!strstr(weapondefid->weapDef->szOverlayName, "claymore")) && (!strstr(weapondefid->weapDef->szOverlayName, "bouncing") && (!strstr(weapondefid->weapDef->szOverlayName, "shock")) && (!strstr(weapondefid->weapDef->szOverlayName, "tactical") && (!strstr(weapondefid->weapDef->szOverlayName, "axe")) && (!strstr(weapondefid->weapDef->szOverlayName, "trophy"))))) {
					int deltaTime = cg->playerstate.commandTime - nade.Delta;
					nade.EndTime = (nade.StartTime - deltaTime);
					color C = color((255 - ((float)nade.EndTime * 0.00)), ((float)nade.EndTime * 0.55), 0, 255);
					//nade.EndTime = 1 - ((float)deltaTime / (1 * 1000));
					DrawShaderPP(ET_ItemPosition.x - 55 / 2, ET_ItemPosition.y, (((float)nade.EndTime - 0.0f) / ((float)nade.StartTime - 0.0f) * 56.f), 5, 0,
						C,
						white, align_left);
				}
			}
		}
	}
}

Vector2 Calc(int N, float Distance, int count) {
	Vector2 ret;
	ret.x = (cg->refdef.Width / 2) + (Sin((N * (360.f / count)) / 180.f * M_PI) * Distance);
	ret.y = (cg->refdef.Height / 2) + (Cos((N * (360.f / count)) / 180.f * M_PI) * Distance);
	return ret;
}

Vector2 Bound;
void DrawCircle() {
	int lineCount = 54;
	for (int a = 0; a <= lineCount; a++) {
		if (a != lineCount)
			Bound = Calc(a, bot.fovs, lineCount);
		DrawLineV(Calc(a, bot.fovs, lineCount), Calc(a + 1, bot.fovs, lineCount), menu->fc, 1);
	}
}

struct Grenade_t {
	color GrenadeCol;
	int movdir;
	DWORD entity;
	std::vector<Vector3> positions;
	float addTime;
	float startTime;
};

class CGrenade {
public:
	CGrenade();
	~CGrenade();
	bool checkGrenades(DWORD ent);
	void addGrenade(Grenade_t grenade);
	void updatePosition(DWORD ent, Vector3 position);
	void draw();
	std::vector<Grenade_t> grenades;
	bool Finished;
private:
	int findGrenade(DWORD ent);
};

int CGrenade::findGrenade(DWORD ent) {
	for (size_t i = 0; i < grenades.size(); i++) {
		if (grenades.at(i).entity == ent)
			return i;
	}
	return 0;
}

CGrenade::CGrenade() {
}

CGrenade::~CGrenade() {
	grenades.clear();
}

bool CGrenade::checkGrenades(DWORD ent) {
	for (Grenade_t grenade : grenades) {
		if (grenade.entity == ent)
			return false;
	}
	return true;
}

void CGrenade::addGrenade(Grenade_t grenade) {
	grenades.push_back(grenade);
}

void CGrenade::updatePosition(DWORD ent, Vector3 position) {
	grenades.at(findGrenade(ent)).positions.push_back(position);
}

void CGrenade::draw() {
	for (size_t i = 0; i < grenades.size(); i++) {
		int deltaTime = cg->playerstate.commandTime - grenades.at(i).startTime;
		if (grenades.at(i).addTime + 20.f < dc.realTime) {
			continue;
		}
		if (grenades.at(i).addTime + 2.5f < dc.realTime) {
			if (grenades.at(i).positions.size() < 1) continue;

			grenades.clear();

			Finished = true;
		}

		for (size_t j = 1; j < grenades.at(i).positions.size(); j++) {
			Vector2 sPosition;
			Vector2 sLastPosition;

			if (WorldPosToScreenPos(grenades.at(i).positions.at(j), &sPosition) && WorldPosToScreenPos(grenades.at(i).positions.at(j - 1), &sLastPosition)) {
				DrawLineV(sPosition, sLastPosition, menu->skin, 2);
			}
		}
	}
}

CGrenade GrenadeClass;
void GrenadeVisuals(int i) {
	if (centity[i].Type == ET_MISSILE) {
		if (((centity[i].State & (1 << 6)) != 0)) {
			if (GrenadeClass.checkGrenades(i)) {
				Grenade_t grenade;
				grenade.GrenadeCol = color(255, 255, 0, 255);
				grenade.movdir = centity[i].movementDir;
				grenade.entity = i;
				grenade.addTime = dc.realTime;
				grenade.startTime = cg->playerstate.commandTime;
				GrenadeClass.addGrenade(grenade);
			} else {
				GrenadeClass.updatePosition(i, centity[i].Origin);
			}
			GrenadeClass.draw();
		}
	}
}

struct  FactionData {
	vec4_t factionColor[10];
	bool initialized;
};

#define Faction ((FactionData*)(0xda39dc))

int BG_GetFactionFromTeam_t[2] = { 0x001b2d0, TOC };
const char* (*BG_GetFactionFromTeam_f)(team_t team, const char* mapName) = (const char* (*)(team_t, const char*))BG_GetFactionFromTeam_t;

int BG_GetFactionColor_t[2] = { 0x001b170, TOC };
void(*BG_GetFactionColor_f)(const char* teamName, Vector4* color) = (void(*)(const char*, Vector4*))BG_GetFactionColor_t;

color BG_GetColor(team_t team) {
	const char* str = BG_GetFactionFromTeam_f(team, Dvar_GetString("party_mapname"));
	color temp;
	BG_GetFactionColor_f(str, (Vector4*)&temp);
	temp.a = 1.0f;
	return temp;
}

void visual_rendermp() {
	playerState_s* playerState = CG_GetPredictedPlayerState(0);

	if (!BG_UsingVehicleWeapon(playerState)) {
		if (cg->health <= 0)return;
	}

	if (bot.aimtype == AIM_TYPE_TRIGGERBOT && bot.bcircle) DrawCircle();

	Vector2 HeadPosition, FootPosition;

	float DF = cg->zoomProgress > 0 ? (70 - cg->zoomProgress * 3) : (70 + cg->spreadMultiplier / 8);

	CG_CompassDrawPlayerMap();

	DrawRadarOutLines(rx, ry, rw, rh, 3);

	CIANiggers.MainHandler();

	if (bot.esp.ballies || bot.esp.baxis) {
		for (int i = 0; i < 1024; i++) {

			DrawNadeFuseTimer(i);

			EntityVisuals(i);

			if (bot.esp.ballies && CG_IsEntityFriendlyNotEnemy(&centity[i])) {
				if (CScr_IsAlive(i)) {
					if (i != cg->clientNum) {

						Vector3 HeadOrigin;
						HeadOrigin = local->playeresp[i].vtagesp[EspBoneIndex[j_head]];
						Vector3 FootOrigin = centity[i].Origin;
						HeadOrigin.z += 12;
						FootOrigin.z -= 5;

						if (centity[i].Type == ET_PLAYER) menu->esp[i] /*= BG_GetColor(cg->clients[i].team);*/ = menu->fn;

						if (bot.esp.bcompass) CG_DrawWarningPointer(i, menu->esp[i], DF, 0.8f);

						if (WorldPosToScreenPos(FootOrigin, &FootPosition) && WorldPosToScreenPos(HeadOrigin, &HeadPosition)) {
							HandleSnapLines(i, &FootPosition, &HeadPosition, menu->esp[i]);
							if (bot.esp.bvangles) DrawVAngles(HeadOrigin, i, menu->esp[i]);
							if (bot.esp.bnames) CG_DrawOverheadNames(0, &centity[i], 1.0f, FullName);
							HandleESPBox(bot.esp.bound, i, FootPosition, HeadPosition, menu->esp[i]);
						}

						if (bot.esp.clienthealth) Drawclientshealth(i, FootPosition, HeadPosition);
					}
				}

				DrawRadarDynamics(i, menu->esp[i], COMPASS_TYPE_PARTIAL);
			}

			else if (bot.esp.baxis && !CG_IsEntityFriendlyNotEnemy(&centity[i])) {
				if (CScr_IsAlive(i)) {
					if (i != cg->clientNum) {

						Vector3 HeadOrigin;
						HeadOrigin = local->playeresp[i].vtagesp[EspBoneIndex[j_head]];
						Vector3 FootOrigin = centity[i].Origin;
						HeadOrigin.z += 12;
						FootOrigin.z -= 5;

						if (centity[i].Type == ET_PLAYER) {
							menu->esp[i] /*= BG_GetColor(cg->clients[i].team);*/ = (((bot.bvisible_esp[i]) ? menu->vis : (bot.bautowall_esp[i]) ? menu->hitble : (centity[i].WeaponID == 89 || centity[i].OldWeapon == 89) ? menu->hb : menu->en));
						}

						if (bot.esp.bcompass) CG_DrawWarningPointer(i, menu->esp[i], DF, 0.8f);

						if (bot.esp.bprox) prox(i);

						if (WorldPosToScreenPos(FootOrigin, &FootPosition) && WorldPosToScreenPos(HeadOrigin, &HeadPosition)) {
							HandleSnapLines(i, &FootPosition, &HeadPosition, menu->esp[i]);
							if (bot.esp.bvangles) DrawVAngles(HeadOrigin, i, menu->esp[i]);
							if (bot.esp.bnames) CG_DrawOverheadNames(0, &centity[i], 1.0f, FullName);
							HandleESPBox(bot.esp.bound, i, FootPosition, HeadPosition, menu->esp[i]);
						}

						if (bot.esp.clienthealth) {
							Drawclientshealth(i, FootPosition, HeadPosition);
						}
					}
				}

				DrawRadarDynamics(i, menu->esp[i], COMPASS_TYPE_PARTIAL);

			}
		}
	}

	if (bot.esp.sprintmeter) draw_sprint_meter();
	if (bot.esp.bhealthbar) HealthBar(cg);
	if (bot.esp.bdynamic) DCrosshair(menu->xh);
}