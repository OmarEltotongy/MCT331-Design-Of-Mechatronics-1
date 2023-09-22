#include "products.h"

Products::Products(uint8_t numberOfProducts): numberOfProducts(numberOfProducts)
{
  
}

static Products* Products::getInstance(uint8_t numberOfProducts)
{
  static Products* instancePtr = nullptr;
  if(nullptr == instancePtr)
  {
    static Products instance(numberOfProducts);
    instancePtr = &instance;
    return instancePtr;
  }
  return nullptr;
}

uint8_t Products::getNumberOfProducts()
{
  return this->numberOfProducts; 
}

uint32_t Products::calculateProductPositionX(uint8_t productMaterial) const
{
  uint8_t curFactorX;
  if(productMaterial)
  {
    curFactorX = metalStored % 2;
  }
  else
  {
    curFactorX = plasticStored % 2;
  }
  return curFactorX * PRODUCT_X_FACTOR + PRODUCT_X_BIAS;
}

uint32_t Products::calculateProductPositionY(uint8_t productMaterial) const
{
  uint8_t curFactorY;
  if(productMaterial)
  {
    curFactorY = metalStored / 2;
    return curFactorY * PRODUCT_METAL_Y_FACTOR + PRODUCT_METAL_Y_BIAS;    
  }
  else
  {
    curFactorY = plasticStored / 2;
    return curFactorY * PRODUCT_PLASTIC_Y_FACTOR + PRODUCT_PLASTIC_Y_BIAS; 
  }
}

void Products::ackProductStored(uint8_t productMaterial)
{
  if(productMaterial)
  {
    this->metalStored += 1;
  }
  else
  {
    this->plasticStored += 1;
  }
}

uint8_t Products::allProductsStored() const
{
  if(metalStored + plasticStored >= numberOfProducts)
  {
    return true;
  }  
  return false;
}