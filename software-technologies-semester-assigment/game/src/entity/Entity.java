package entity;

import java.awt.image.BufferedImage;

public class Entity {

	public int worldX, worldY;
	public int Speed;
	public int Life;

	public BufferedImage move0, move1, move2, move3, move4, move5, move6, move7, move8, move9,idle;
	public String directions;

	public int spriteCounter = 0;
	public int spriteNum = 1;
}
