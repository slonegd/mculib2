библиотеки для работы с микроконтроллерами

готово:

    pin_hal.h - полностью статические классы пинов микроконтроллера
                каждому пину свой класс, который можно передавать в качестве параметра шаблона

    timers.h - классы для работы с программными таймерами (точность 1мс)

    flash_hal.h - имитация еепром на флеше. Можно сохранять любую структуру
                  размерм не более 255 байт на одном секторе