// Fügen Sie hier Ihren Code ein:
  // 1.
  function Point(x, y) {
    this.x = x;
    this.y = y;
  }
  // 2.
  Point.prototype.toString = function() {
    return "Point(" + this.x + "," + this.y + ")";
  }
  // 3.
  Point.prototype.add = function(other) {
    return new Point((this.x + other.x), (this.y + other.y)); 
  }
  // 4. 
  Point.prototype.isEqualTo = function(other) {
    if(this.x === other.x && this.y === other.y) {
      return true
    }
    else {
      return false
    }
  }
  // 5.
  function GeometryObject() {

  }
  // 6.
  Object.setPrototypeOf(Point.prototype, GeometryObject.prototype);
  
  // Beispiel für die Verwendung:
  var p1 = new Point(3,1);
  var p2 = new Point(2,4);
  var p3 = p1.add(p2);
  console.log(p1 + " + " + p2 + " = " + p3);
  console.log(p3 + ".isEqualTo(new Point(5,5)) = " + p3.isEqualTo(new Point(5,5)));
  console.log("(p1 instanceof Point) = " + (p1 instanceof Point));
  console.log("(p1 instanceof GeometryObject) = " + (p1 instanceof GeometryObject));
  console.log("(p1.constructor === Point) = " + (p1.constructor === Point));
  /* 
  Ausgabe:
  Point(3,1) + Point(2,4) = Point(5,5)
  Point(5,5).isEqualTo(new Point(5,5)) = true
  (p1 instanceof Point) = true
  (p1 instanceof GeometryObject) = true
  (p1.constructor === Point) = true
  */