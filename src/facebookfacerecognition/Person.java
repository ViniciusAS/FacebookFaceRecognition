package facebookfacerecognition;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.scene.image.Image;

/**
 *
 * @author Vinicius Santos
 */
public class Person {

    private final StringProperty name;
    private Image image;
    
    public Person() {
        name = new SimpleStringProperty("");
        image = null;
    }

    public Person(StringProperty name, Image image) {
        this.name = name;
        this.image = image;
    }

    public Person(Image image) {
        this.name = new SimpleStringProperty("");
        this.image = image;
    }    
    
    public Person(String name, Image image) {
        this.name = new SimpleStringProperty(name);
        this.image = image;
    }

    public StringProperty nameProperty(){
        return name;
    }
    
    public Image getImage() {
        return image;
    }

    public String getName() {
        return name.getValue();
    }
    
    public void setImage(Image image) {
        this.image = image;
    }

    public void setName(String name) {
        this.name.setValue(name);
    }
    
}
