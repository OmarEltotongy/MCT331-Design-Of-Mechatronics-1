#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <Arduino.h>

#define PRODUCT_X_FACTOR            6000
#define PRODUCT_X_BIAS              -1500 

#define PRODUCT_PLASTIC_Y_FACTOR    290
#define PRODUCT_PLASTIC_Y_BIAS      750 

#define PRODUCT_METAL_Y_FACTOR      320
#define PRODUCT_METAL_Y_BIAS        1420 

class Products{
private:

  uint8_t numberOfProducts; 
  uint8_t metalStored;
  uint8_t plasticStored;
  Products(uint8_t numberOfProducts);
  
public:

  static Products* getInstance(uint8_t numberOfProducts);
  uint8_t getNumberOfProducts();
  uint32_t calculateProductPositionX(uint8_t productMaterial) const;
  uint32_t calculateProductPositionY(uint8_t productMaterial) const;
  void ackProductStored(uint8_t productMaterial);
  uint8_t allProductsStored() const;

};

#endif