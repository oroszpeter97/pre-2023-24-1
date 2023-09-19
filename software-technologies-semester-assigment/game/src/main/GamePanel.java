package main;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

import entity.Player;
import tile.TileManager;


public class GamePanel extends JPanel implements Runnable {

	// screen settings
	final int originalTitleSize = 16;
	final int scale = 3;
	
	public final int characterSizeCol= 40*2;
	public final int characterSizeRow= 30*2;
	public final int tileSize = originalTitleSize * scale;
	public final int maxScreenCol = 30;
	public final int maxScreenRow = 25;
	public final int screenWidth = tileSize * maxScreenCol;
	public final int screenHeight = tileSize * maxScreenRow;

	// World settings
	public final int maxWorldCol = 50;
	public final int maxWorldRow = 50;
	public final int worldWidth = tileSize * maxWorldCol;
	public final int worldHeight = tileSize * maxWorldRow;

	KeyHandler keyH = new KeyHandler();
	TileManager tileM = new TileManager(this);
	Thread gameThread;
	public Player player = new Player(this, keyH);

	// "fps"
	int updateTimes = 60;

	// player def lock

	// int playerX = 150;
	// int playerY = 100;
	// int playerSpeed = 2;

	public GamePanel() {
		this.setPreferredSize(new Dimension(screenWidth, screenHeight));
		this.setBackground(Color.black);
		this.setDoubleBuffered(true);
		this.addKeyListener(keyH);
		this.setFocusable(true);
	}

	public void startGameThread() {
		gameThread = new Thread(this);
		gameThread.start();
	}

	@Override
	public void run() {
		while (gameThread != null) {

			double drawInterval = 1000000000 / updateTimes;
			long currenTime = System.nanoTime();
			double nextDrawnTime = currenTime + drawInterval;

			update();

			repaint();

			try {
				double remainingTime = nextDrawnTime - currenTime;
				remainingTime = remainingTime / 1000000;
				if (remainingTime < 0) {
					remainingTime = 0;
				}
				Thread.sleep((long) remainingTime);
				nextDrawnTime += drawInterval;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	public void update() {

		player.update();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		tileM.draw(g2);
		player.draw(g2);
		g2.dispose();
	}
}
