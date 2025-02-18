from aiogram.types import Message
from aiogram.filters import Command, CommandStart
from aiogram import Router
from aiogram.enums import ChatAction
from aiogram.fsm.state import State, StatesGroup
from aiogram.fsm.context import FSMContext

class Reg(StatesGroup):
    name = State()
    arg = State()
    number = State()
    parol = State()

user_router = Router()

@user_router.message(CommandStart())
async def cmd_start(message: Message, state: FSMContext):
    await message.bot.send_chat_action(chat_id=message.from_user.id, action=ChatAction.TYPING)
    await state.set_state(Reg.name)
    open('catsdate.txt', 'w').close()
    await message.answer('Привет!, введи свое имя')

@user_router.message(Reg.name)
async def reg_name(message: Message, state: FSMContext):
    await state.update_data(name=message.text)
    with open('catsdate.txt', 'a') as f:
        f.write(f'{message.text} ')
    await state.set_state(Reg.arg)
    await message.answer('Будем регистрироваться полностью?')

@user_router.message(Reg.arg)
async def reg_agreement(message: Message, state: FSMContext):
    if message.text.lower() == "да":
        await state.set_state(Reg.number)
        await message.answer('Введи свой номер, пожалуйста')
    else:
        await message.answer('Все за регистрацию.')
        await state.clear()

@user_router.message(Reg.number)
async def reg_number(message: Message, state: FSMContext):
    await state.update_data(number=message.text)
    await state.set_state(Reg.parol)
    await message.answer('Введи свой пароль, пожалуйста')

@user_router.message(Reg.parol)
async def reg_p(message: Message, state: FSMContext):
    with open('catsdate.txt', 'a') as f:
        f.write(f'{message.text} ')
    await message.answer("Полная регистрация завершена.")
    await state.clear()

@user_router.message(Command("pull"))
async def cmd_pull(message: Message):
    await message.bot.send_chat_action(chat_id=message.from_user.id, action=ChatAction.TYPING)
    await message.answer("Введи имя и пароль (если регистрировался полностью) без пробела.")

@user_router.message()
async def echo(message: Message):
    await message.bot.send_chat_action(chat_id=message.from_user.id, action=ChatAction.TYPING)
    with open('catsdate.txt') as file:
        c = file.read().strip().split()
    if (message.text) == ''.join(c):
        await message.answer('Данные верны, держи подарочек ❤️')
        await message.reply_sticker('CAACAgIAAxkBAAEN1btntKBRRr_UK-aAyAeqZA6GvplkuAACNlsAAjO0AUgE5folOi7rbTYE')
    else:
        await message.answer('Ошибка: неверные данные')
