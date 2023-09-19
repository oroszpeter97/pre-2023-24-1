package entity;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import main.GamePanel;
import main.KeyHandler;

public class Player extends Entity {

	GamePanel gp;
	KeyHandler keyH;
	public final int screenX;
	public final int screenY;

	public Player(GamePanel gp, KeyHandler keyH) {
		this.gp = gp;
		this.keyH = keyH;
		screenX = gp.screenWidth / 2 - (gp.tileSize / 2);
		screenY = gp.screenHeight / 2 - (gp.tileSize / 2);
		setDefaultValues();
		getPlayerImage();
	}

	public void setDefaultValues() {
		worldX = gp.tileSize * 23;
		worldY = gp.tileSize * 21;
		Speed = 4;
		directions = "idle";
		Life = 100;
	}

	public void getPlayerImage() {
		try {
			move0 = ImageIO.read(getClass().getResourceAsStream("/player/tile000.png"));
			move1 = ImageIO.read(getClass().getResourceAsStream("/player/tile001.png"));
			move2 = ImageIO.read(getClass().getResourceAsStream("/player/tile002.png"));
			move3 = ImageIO.read(getClass().getResourceAsStream("/player/tile003.png"));
			move4 = ImageIO.read(getClass().getResourceAsStream("/player/tile004.png"));
			move5 = ImageIO.read(getClass().getResourceAsStream("/player/tile005.png"));
			move6 = ImageIO.read(getClass().getResourceAsStream("/player/tile006.png"));
			move7 = ImageIO.read(getClass().getResourceAsStream("/player/tile007.png"));
			move8 = ImageIO.read(getClass().getResourceAsStream("/player/tile008.png"));
			move9 = ImageIO.read(getClass().getResourceAsStream("/player/tile009.png"));
			idle = ImageIO.read(getClass().getResourceAsStream("/player/idle.png"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void update() {
		if (keyH.upPressed == true || keyH.downPressed == true || keyH.leftPressed == true
				|| keyH.rightPressed == true) {

			if (keyH.upPressed == true) {
				if (directions == "left" || directions == "leftidle") {
					directions = "left";
				} else {
					directions = "right";
				}
				worldY -= Speed;

			}
			if (keyH.downPressed == true) {
				if (directions == "left" || directions == "leftidle") {
					directions = "left";
				} else {
					directions = "right";
				}
				worldY += Speed;

			}
			if (keyH.leftPressed == true) {
				directions = "left";
				worldX -= Speed;

			}
			if (keyH.rightPressed == true) {
				directions = "right";
				worldX += Speed;

			}

			spriteCounter++;
			if (spriteCounter > 4) {
				spriteNum++;
				if (spriteNum > 9) {
					spriteNum = 0;
				}
				spriteCounter = 0;
			}

		} else {
			if (directions == "left" || directions == "leftidle") {
				directions = "leftidle";
			} else {
				directions = "idle";
			}
		}

	}

	public void draw(Graphics2D g2) {

		BufferedImage image = null;
		BufferedImage[] moveList = { move0, move1, move2, move3, move4, move5, move6, move7, move8, move9 };
		image = moveList[spriteNum];
		if (directions == "right") {
			g2.drawImage(image, screenX, screenY, gp.characterSizeRow, gp.characterSizeCol, null);
		} else if (directions == "left") {
			g2.drawImage(image, screenX + gp.characterSizeRow, screenY, -gp.characterSizeRow, gp.characterSizeCol,
					null);
		} else if (directions == "leftidle") {
			g2.drawImage(idle, screenX + gp.characterSizeRow, screenY, -gp.characterSizeRow, gp.characterSizeCol, null);
		} else {
			g2.drawImage(idle, screenX, screenY, gp.characterSizeRow, gp.characterSizeCol, null);
		}

		g2.setColor(Color.white);
		g2.drawString("Élet:" + Life, screenX, screenY);
	}
}
