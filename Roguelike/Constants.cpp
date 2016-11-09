#include "Constants.h"
#include <windows.h>

int Constants :: defaultAttack = GetPrivateProfileInt("Defaults", "Attack", 0, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultHitRadius = GetPrivateProfileInt("Defaults", "HitRadius", 1, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultHP = GetPrivateProfileInt("Defaults", "HP", 1, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultSightRadius = GetPrivateProfileInt("Defaults", "SightRadius", 5, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultSpeed = GetPrivateProfileInt("Defaults", "Speed", 3, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultShootUp = GetPrivateProfileInt("Defaults", "ShootUp", 450, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultShootDown = GetPrivateProfileInt("Defaults", "ShootDown", 456, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultShootLeft = GetPrivateProfileInt("Defaults", "ShootLeft", 452, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: defaultShootRight = GetPrivateProfileInt("Defaults", "ShootRight", 454, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: defaultIcon = '?';

char Constants :: defaultUp = 0;
char Constants :: defaultDown = 0;
char Constants :: defaultLeft = 0;
char Constants :: defaultRight = 0;
char Constants :: defaultMeleeAttack = 0;
char Constants :: restart = 0;
char Constants :: defaultUseItem1 = 0;
char Constants :: defaultUseItem2 = 0;
char Constants :: defaultUseItem3 = 0;
char Constants :: defaultUseLastItem = 0;

int Constants :: dragonAttack = GetPrivateProfileInt("Dragon", "Attack", Constants :: defaultAttack, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: dragonHP = GetPrivateProfileInt("Dragon", "HP", Constants :: defaultHP, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: dragonIcon = Constants :: defaultIcon;

char Constants :: floor = '?';

int Constants :: knightAttack = GetPrivateProfileInt("Knight", "Attack", Constants :: defaultAttack, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: knightHitRadius = GetPrivateProfileInt("Knight", "HitRadius", Constants :: defaultHitRadius, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: knightHP = GetPrivateProfileInt("Knight", "HP", Constants :: defaultHP, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: InventorySize = GetPrivateProfileInt("Knight", "InventorySize", 3, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: knightIcon = Constants :: defaultIcon;

int Constants :: princessAttack = GetPrivateProfileInt("Princess", "Attack", Constants :: defaultAttack, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: princessHP = GetPrivateProfileInt("Princess", "HP", Constants :: defaultHP, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: princessIcon = Constants :: defaultIcon;

int Constants :: projectileAttack = GetPrivateProfileInt("Projectile", "Attack", Constants :: defaultAttack, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: projectileHP = GetPrivateProfileInt("Projectile", "HP", Constants :: defaultHP, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: projectileSpeed = GetPrivateProfileInt("Projectile", "Speed", Constants :: defaultSpeed, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: projectileIcon = Constants :: defaultIcon;

int Constants :: zombieAttack = GetPrivateProfileInt("Zombie", "Attack", Constants :: defaultAttack, "C:/Users/Default/Documents/RogueLike/constants.ini");
int Constants :: zombieHP = GetPrivateProfileInt("Zombie", "HP", Constants :: defaultHP, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: zombieIcon = Constants :: defaultIcon;

int Constants :: healkitHP = GetPrivateProfileInt("Healkit", "HP", Constants :: defaultHP, "C:/Users/Default/Documents/RogueLike/constants.ini");
char Constants :: healkitIcon = Constants::defaultIcon;

char Constants :: moveUp = 0;
char Constants :: moveDown = 0;
char Constants :: moveLeft = 0;
char Constants :: moveRight = 0;
char Constants :: meleeAttack = 0;
char Constants :: shootUp = 0;
char Constants :: shootDown = 0;
char Constants :: shootLeft = 0;
char Constants :: shootRight = 0;
char Constants :: useItem1 = 0;
char Constants :: useItem2 = 0;
char Constants :: useItem3 = 0;
char Constants :: useLastItem = 0;

Constants::Constants()
{
	char buff[2];
	GetPrivateProfileString("Defaults", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultIcon = buff[0];

	GetPrivateProfileString("Defaults", "Up", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultUp = buff[0];

	GetPrivateProfileString("Defaults", "Down", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultDown = buff[0];

	GetPrivateProfileString("Defaults", "Left", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultLeft = buff[0];

	GetPrivateProfileString("Defaults", "Right", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultRight = buff[0];

	GetPrivateProfileString("Defaults", "Attack", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultMeleeAttack = buff[0];

	GetPrivateProfileString("Defaults", "Restart", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: restart = buff[0];

	GetPrivateProfileString("Defaults", "UseItem1", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultUseItem1 = buff[0];

	GetPrivateProfileString("Defaults", "UseItem2", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultUseItem2 = buff[0];

	GetPrivateProfileString("Defaults", "UseItem3", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultUseItem3 = buff[0];

	GetPrivateProfileString("Defaults", "UseLastItem", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: defaultUseLastItem = buff[0];

	GetPrivateProfileString("Drawable", "Floor", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: floor = buff[0];

	GetPrivateProfileString("Dragon", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: dragonIcon = buff[0];

	GetPrivateProfileString("Knight", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: knightIcon = buff[0];

	GetPrivateProfileString("Princess", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants ::princessIcon = buff[0];

	GetPrivateProfileString("Projectile", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: projectileIcon = buff[0];

	GetPrivateProfileString("Zombie", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: zombieIcon = buff[0];

	GetPrivateProfileString("Healkit", "Pic", "??", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: healkitIcon = buff[0];

	GetPrivateProfileString("Controls", "Up", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: moveUp = buff[0];

	GetPrivateProfileString("Controls", "Down", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: moveDown = buff[0];

	GetPrivateProfileString("Controls", "Left", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: moveLeft = buff[0];

	GetPrivateProfileString("Controls", "Right", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: moveRight = buff[0];

	GetPrivateProfileString("Controls", "Attack", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: meleeAttack = buff[0];

	GetPrivateProfileString("Controls", "ShootRight", "", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	if (!strcmp(buff, "")) {
		buff[0] = Constants :: defaultShootRight;
	}
	Constants :: shootRight = buff[0];

	GetPrivateProfileString("Controls", "ShootLeft", "", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	if (!strcmp(buff, "")) {
		buff[0] = Constants :: defaultShootLeft;
	}
	Constants :: shootLeft = buff[0];

	GetPrivateProfileString("Controls", "ShootUp", "", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	if (!strcmp(buff, "")) {
		buff[0] = Constants :: defaultShootUp;
	}
	Constants :: shootUp = buff[0];

	GetPrivateProfileString("Controls", "ShootDown", "", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	if (!strcmp(buff, "")) {
		buff[0] = Constants :: defaultShootDown;
	}
	Constants :: shootDown = buff[0];

	GetPrivateProfileString("Controls", "UseItem1", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: useItem1 = buff[0];

	GetPrivateProfileString("Controls", "UseItem2", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: useItem2 = buff[0];

	GetPrivateProfileString("Controls", "UseItem3", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: useItem3 = buff[0];

	GetPrivateProfileString("Controls", "UseLastItem", "\0\0", buff, 2, "C:/Users/Default/Documents/RogueLike/constants.ini");
	Constants :: useLastItem = buff[0];
}

Constants::~Constants()
{
}
