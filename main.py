import asyncio
import logging

from aiogram import Bot, Dispatcher

from catttttt.h import user_router


async def main():
    bot = Bot(token="")
    dp = Dispatcher()
    dp.include_router(router=user_router)
    await dp.start_polling(bot)



if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print('Exit')
