#ifndef INVENTORY_H
#define INVENTORY_H

#include "entity.h"

#include "gamedefs.h"
#include "items.h"

#include <memory>
#include <iostream>

class Inventory
{
	public:


	std::vector<std::shared_ptr<Entity>> items;

	std::vector<ent> slots;
	std::vector<int> slots_count;
	int max_slots = 5;

	int selected_slot = 0;

	Inventory()
	{
		slots.insert(slots.begin(), max_slots, ent::none);
		slots_count.insert(slots_count.begin(), max_slots, 0);
	};


	bool HasSlotFor(Entity &entity) const
	{
		ent e = entity.entitydef;

		for(int i=0; i< max_slots; i++)
		{
			if (slots[i] == e) return true;
		}

		return false;
	}


	bool HasEmptySlot() const
	{
		for(int i=0; i< max_slots; i++)
		{
			if (slots[i] == ent::none) return true;
		}
		return false;
	}


	int GetSlotFor(Entity &entity) const
	{
		ent e = entity.entitydef;

		for(int i=0; i< max_slots; i++)
		{
			if (slots[i] == e) return i;
		}

		if (HasEmptySlot())
		{
			//prefer to use the selected slot to fill up
			if (slots[selected_slot] == ent::none) return selected_slot;

			for(int i=0; i< max_slots; i++)
			{
				if (slots[i] == ent::none) return i;
			}
		}

		throw std::logic_error("Inventory::GetSlotFor(): Couldn't find slot");
	}

	void IncSlot(Entity &item)
	{
		ent def = item.entitydef;
		int s = GetSlotFor(item);

		if (slots[s] != def)
		{
			slots[s] = def;
			slots_count[s] = 0;
		}

		slots_count[s]++;
	}

	void DecSlot(Entity &item)
	{
		ent def = item.entitydef;
		int s = GetSlotFor(item);

		if (slots[s] != def) { throw std::logic_error("Inventory::DecSlot() - unexpected item in inventory slot"); }

		slots_count[s]--;

		if (slots_count[s] == 0)
		{
			slots[s] = ent::none;
		}
	}

	void Move(std::shared_ptr<Entity> &&item)
	{
		IncSlot(*item);

		items.push_back(std::move(item));
	}


	std::shared_ptr<Entity> PopBack()
	{
		std::shared_ptr<Entity> ent;

		if (items.size() > 0)
		{
			ent = items.back();
			items.pop_back();
			DecSlot(*ent);
		}

		return std::move(ent);
	}

	std::shared_ptr<Entity> PopFromSlot()
	{
		return PopFromSlot(selected_slot);
	}

	std::shared_ptr<Entity> PopFromSlot(int slot)
	{
		ent looking_for = slots[slot];

		//std::cout << "PopFromSlot(" << slot << ") = " << GetNameForEntity(looking_for) << std::endl;

		std::shared_ptr<Entity> ent;

		for(int i=0; i< items.size(); i++)
		{
			if (items[i]->entitydef == looking_for)
			{
				ent = std::move(items[i]);
				items.erase(items.begin() + i);
				DecSlot(*ent);
				break;
			}
		}

		return std::move(ent);
	}


	bool CanPickup(std::shared_ptr<Entity> &e) const
	{
		return HasEmptySlot() or HasSlotFor(*e);
	}


	int CountCoins() const
	{
		int tally = 0;

		for(const auto &e : items)
		{
			const Coin* c = dynamic_cast<const Coin*>(e.get());
			if (c)
			{
				tally += c->coin_value;
			}
		}

		return tally;
	}

	void ChangeSlot(int i)
	{
		selected_slot = i;
	}

	int GetSelectedSlot() const { return selected_slot; }

};



#endif // INVENTORY_H

