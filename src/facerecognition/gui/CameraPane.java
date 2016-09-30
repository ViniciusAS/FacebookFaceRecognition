package facerecognition.gui;

import facerecognition.opencv.ElementDetector;
import facebookfacerecognition.camera.ObservableCamera;
import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Pos;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import org.opencv.core.Mat;
import org.opencv.core.Rect;

/**
 *
 * @author Vinicius Santos
 */
public class CameraPane extends StackPane implements Observer {
    
    private final ElementDetector elementDetector;
    
    private final Canvas canvasImage;
    private final Canvas canvasRects;
    private final GraphicsContext g2DImage;
    private final GraphicsContext g2DRects;
    
    private final List<OnFaceDetectionListener> onFaceDetectionListeners;
    
    public CameraPane() {
        onFaceDetectionListeners = new ArrayList<>();
        
        elementDetector = new ElementDetector(ElementDetector.Element.FRONTAL_FACE_ALT_TREE);
        
        this.setMinWidth(  800 );
        this.setMinHeight( 500 );
        
        this.setAlignment(Pos.CENTER);
        this.heightProperty().addListener(new SizeChangeListener());
        this.widthProperty().addListener(new SizeChangeListener());
        
        canvasImage = new Canvas();
        canvasRects = new Canvas();
        g2DImage = canvasImage.getGraphicsContext2D();
        g2DRects = canvasRects.getGraphicsContext2D();
        
        g2DRects.setStroke(Color.GREEN);
        
        this.getChildren().addAll( canvasImage, canvasRects );
        fitElements();
    }
    
    private void fitElements(){
        Platform.runLater(() -> {
            // image
            canvasImage.setWidth(  this.getWidth()  );
            canvasImage.setHeight( this.getHeight() );
            // rects
            canvasRects.setWidth(  this.getWidth()  );
            canvasRects.setHeight( this.getHeight() );
        });
    }
    
    @Override
    public void update(Observable o, Object o1)
    {
        if ( !( o instanceof ObservableCamera ) )
        {
            return;
        }
        ObservableCamera cameraSubject = (ObservableCamera) o;
        updateFaces(
            cameraSubject.getImage(),
            cameraSubject.getMat()
        );
    }
    
//    private int count = 0;
    private void updateFaces(Image image, Mat mat){
        
        g2DImage.clearRect(0, 0, getWidth(), getHeight());
        g2DImage.drawImage(image, this.getWidth(), 0, -this.getWidth(), this.getHeight());
        
//        if ( count++%3 == 0 ) {
            final long t = System.currentTimeMillis();
            elementDetector.detectPositions(mat, (List<Rect> rectList) ->
                {
                    List<Rect> rectsSave = new ArrayList<>();
                    for ( Rect r : rectList ){
                        rectsSave.add(
                            new Rect(
                                r.x, r.y,
                                r.width, r.height
                            )
                        );
                    }
                    for ( OnFaceDetectionListener l : onFaceDetectionListeners )
                    {
                        if ( l != null )
                        {
                            l.facesDetected( image, rectsSave );
                        }
                    }
                    
                    double propHorizontal = this.getWidth() / image.getWidth();
                    double propVertical   = this.getHeight() / image.getHeight();

                    for (Rect rect : rectList) {
                        rect.x *= propHorizontal;
                        rect.y *= propVertical;
                        rect.width *= propHorizontal;
                        rect.height *= propVertical;
                    }

                    System.out.print("detection time: "+ (System.currentTimeMillis()-t));

                    System.out.println(";  detections: "+rectList.size());

                    Platform.runLater(() -> {
                        g2DRects.clearRect(0, 0, getWidth(), getHeight());
                        for (Rect rect : rectList) {
                            g2DRects.strokeRect(
                                CameraPane.this.getWidth()-rect.x-rect.width,
                                rect.y,
                                rect.width, rect.height
                            );
                        }
                    });
                }
            );
//        }
    }
    
    public void addOnFaceDetectionListener(OnFaceDetectionListener onFaceDetectionListener){
        onFaceDetectionListeners.add( onFaceDetectionListener );
    }
    
    public interface OnFaceDetectionListener {
        public void facesDetected(Image image, List<Rect> rects);
    }
    
    private class SizeChangeListener implements ChangeListener<Number>{
        @Override
        public void changed(ObservableValue<? extends Number> ov, Number old, Number neww)
        {
            fitElements();
        }
        
    }
    
}
