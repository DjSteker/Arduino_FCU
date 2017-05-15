void AltitudeUpdate(){
  if(settleDown)
    Height = BMP180_GetAltitude() - Init_Altitude;
}

