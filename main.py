import asyncio
import logging

from aiogram import Bot, Dispatcher

from catttttt.h import user_router


async def main():
    bot = Bot(token="7405840785:AAFDUsIG9H25_-2VO_O7nZBeUIycekJvkMA")
    dp = Dispatcher()
    dp.include_router(router=user_router)
    await dp.start_polling(bot)



if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print('Exit')
