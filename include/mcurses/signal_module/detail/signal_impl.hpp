#ifndef SIGNAL_IMPL_HPP
#define SIGNAL_IMPL_HPP

#include "../position.hpp"
#include "../connection.hpp"
#include "connection_impl.hpp"
#include "placeholder_template.hpp"
#include "slot_iterator.hpp"

#include <cstddef>
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <functional>

// Forward Declarations
namespace mcurses
{
	template <typename Signature>
	class connection_impl;
}

namespace mcurses
{

template <typename Signature,
		  typename Combiner,
		  typename Group,
		  typename GroupCompare,
		  typename SlotFunction>
class signal_impl;

template <typename Ret, typename ... Args,
		  typename Combiner,
		  typename Group,
		  typename GroupCompare,
		  typename SlotFunction>
class signal_impl<Ret(Args...), Combiner, Group, GroupCompare, SlotFunction> {
public:
	// Types
	typedef typename Combiner::result_type 	result_type;
	typedef Ret(signature_type)(Args...) ;
	typedef Group group_type;
	typedef GroupCompare group_compare_type;
	typedef std::vector<std::shared_ptr<connection_impl<signature_type>>> positioned_connection_container_type;
	typedef std::map<group_type, positioned_connection_container_type, group_compare_type> grouped_connection_container_type;
	typedef Combiner combiner_type;
	typedef SlotFunction slot_function_type;
	typedef mcurses::slot<signature_type, slot_function_type> slot_type;
	typedef mcurses::slot<Ret(const mcurses::connection&, Args...)> extended_slot_type;


	signal_impl(const combiner_type& combiner, const group_compare_type& group_compare)
	:combiner_{combiner}
	{}

	signal_impl(const signal_impl&) = default;
	signal_impl(signal_impl&& x) = default;
	signal_impl& operator=(const signal_impl&) = default;
	signal_impl& operator=(signal_impl&& x) = default;

	connection connect(const slot_type& s, position pos)
	{
		auto c = std::make_shared<connection_impl<signature_type>>(s);
		if(pos == position::at_front)
		{
			at_front_connections_.push_back(c);
			return connection(c);
		}

		if(pos == position::at_back)
		{
			at_back_connections_.push_back(c);
			return connection(c);
		}
		return connection();
	}

	connection connect(const group_type& g, const slot_type& s, position pos)
	{
		auto c = std::make_shared<connection_impl<signature_type>>(s);
		if(pos == position::at_front)
		{
			grouped_connections_[g].insert(std::begin(grouped_connections_), c);
			return connection(c);
		}
		if(pos == position::at_back)
		{
			grouped_connections_[g].push_back(c);
			return connection(c);
		}
		return connection();
	}

	connection connect_extended(const extended_slot_type& es, position pos)
	{
		auto conn_impl = std::make_shared<connection_impl<signature_type>>();
		connection conn = connection(conn_impl);
		conn_impl->get_slot().slot_function() = bind_connection(es.slot_function(), conn);
		for(std::weak_ptr<void>& wp : es.get_tracked_container())	// copy over tracked items
		{
			conn_impl->get_slot().track(wp);
		}

		if(pos == position::at_front)
		{
			at_front_connections_.push_back(conn_impl);
			return conn;
		}

		if(pos == position::at_back)
		{
			at_back_connections_.push_back(conn_impl);
			return conn;
		}
		return connection();
	}

	connection connect_extended(const group_type& g, const extended_slot_type& es, position pos)
	{
		auto conn_impl = std::make_shared<connection_impl<signature_type>>();
		connection conn = connection(conn_impl);
		conn_impl->get_slot().slot_function() = bind_connection(es.slot_function(), conn);
		for(std::weak_ptr<void>& wp : es.get_tracked_container())	// copy over tracked items
		{
			conn_impl->get_slot().track(wp);
		}

		if(pos == position::at_front)
		{
			grouped_connections_[g].insert(std::begin(grouped_connections_), conn_impl);
			return conn;
		}
		if(pos == position::at_back)
		{
			grouped_connections_[g].push_back(conn_impl);
			return conn;
		}
		return connection();
	}

	void disconnect(const group_type& g)
	{
		for(auto& ci_ptr : grouped_connections_[g])
		{
			ci_ptr->disconnect();
		}
		// It should be safe to destroy the vector at this key; g.
	}

	template <typename S>
	void disconnect(const S& s)
	{	// maybe go through and change these to for_each or something...
		for(auto& ci_ptr : at_front_connections_)
		{
			if(ci_ptr->get_slot().slot_function() == s)
			{
				ci_ptr->disconnect();
			}
		}

		for(auto& kv : grouped_connections_)
		{			// vector
			for(auto& ci_ptr : kv.second)
			{
				if(ci_ptr->get_slot().slot_function() == s)
				{
					ci_ptr->disconnect();
				}
			}
		}

		for(auto& ci_ptr : at_back_connections_)
		{
			if(ci_ptr->get_slot().slot_function() == s)
			{
				ci_ptr->disconnect();
			}
		}
	}

	void disconnect_all_slots()
	{
		for(auto& ci_ptr : at_front_connections_)
		{
			ci_ptr->disconnect();
		}

		for(auto& kv : grouped_connections_)
		{			// vector
			for(auto& ci_ptr : kv.second)
			{
				ci_ptr->disconnect();
			}
		}

		for(auto& ci_ptr : at_back_connections_)
		{
			ci_ptr->disconnect();
		}
	}

	bool empty() const
	{
		for(auto& ci_ptr : at_front_connections_)
		{
			if(!ci_ptr->disconnected())
			{
				return false;
			}
		}

		for(auto& kv : grouped_connections_)
		{			// vector
			for(auto& ci_ptr : kv.second)
			{
				if(!ci_ptr->disconnected())
				{
					return false;
				}
			}
		}

		for(auto& ci_ptr : at_back_connections_)
		{
			if(!ci_ptr->disconnected())
			{
				return false;
			}
		}
		// no slots that are not disconnected
		return true;
	}

	std::size_t num_slots() const
	{
		std::size_t size{0};
		for(auto& ci_ptr : at_front_connections_)
		{
			if(!ci_ptr->disconnected())
			{
				++size;
			}
		}

		for(auto& kv : grouped_connections_)
		{			// vector
			for(auto& ci_ptr : kv.second)
			{
				if(!ci_ptr->disconnected())
				{
					++size;
				}
			}
		}

		for(auto& ci_ptr : at_back_connections_)
		{
			if(!ci_ptr->disconnected())
			{
				++size;
			}
		}
		return size;
	}

	result_type operator()(Args&&... args)
	{
		std::vector<slot_iterator<Ret(Args...)>> iter_container;
		for(auto& c : at_front_connections_)
		{
			if(c->connected() && !c->blocked())
			{
				iter_container.push_back(slot_iterator<Ret(Args...)>(c->get_slot(), std::forward<Args>(args)...));
			}
		}

		for(auto& kv : grouped_connections_)
		{
			for(auto& c : kv.second)
			{
				if(c->connected() && !c->blocked())
				{
					iter_container.push_back(slot_iterator<Ret(Args...)>(c->get_slot(), std::forward<Args>(args)...));
				}
			}
		}

		for(auto& c : at_back_connections_)
		{
			if(c->connected() && !c->blocked())
			{
				iter_container.push_back(slot_iterator<Ret(Args...)>(c->get_slot(), std::forward<Args>(args)...));
			}
		}
		iter_container.push_back(slot_iterator<Ret(Args...)>());	// one past end iterator
		return combiner_(iter_container.front(), iter_container.back());
	}

	result_type operator()(Args&&... args) const
	{
		std::vector<slot_iterator<Ret(Args...)>> iter_container;
		for(auto& c : at_front_connections_)
		{
			if(c->connected() && !c->blocked())
			{
				iter_container.push_back(slot_iterator<Ret(Args...)>(c->get_slot(), std::forward<Args>(args)...));
			}
		}

		for(auto& kv : grouped_connections_)
		{
			for(auto& c : kv.second)
			{
				if(c->connected() && !c->blocked())
				{
					iter_container.push_back(slot_iterator<Ret(Args...)>(c->get_slot(), std::forward<Args>(args)...));
				}
			}
		}

		for(auto& c : at_back_connections_)
		{
			if(c->connected() && !c->blocked())
			{
				iter_container.push_back(slot_iterator<Ret(Args...)>(c->get_slot(), std::forward<Args>(args)...));
			}
		}
		iter_container.push_back(slot_iterator<Ret(Args...)>());	// one past end iterator
		const combiner_type const_comb = combiner_;
		return const_comb(iter_container.front(), iter_container.back());
	}

	// void void_specialization_operator_call(Args&&... args) const
	// {
	// 	for(auto& ci_ptr : at_front_connections_)
	// 	{
	// 		if(ci_ptr->connected() && !ci_ptr->blocked())
	// 		{
	// 			ci_ptr->get_slot()(std::forward<Args>(args)...);
	// 		}
	// 	}

	// 	for(auto& kv : grouped_connections_)
	// 	{
	// 		for(auto& ci_ptr : kv.second)
	// 		{
	// 			if(ci_ptr->connected() && !ci_ptr->blocked())
	// 			{
	// 				ci_ptr->get_slot()(std::forward<Args>(args)...);
	// 			}
	// 		}
	// 	}

	// 	for(auto& ci_ptr : at_back_connections_)
	// 	{
	// 		if(ci_ptr->connected() && !ci_ptr->blocked())
	// 		{
	// 			ci_ptr->get_slot()(std::forward<Args>(args)...);
	// 		}
	// 	}
	// 	return;
	// }

	combiner_type combiner() const
	{
		return combiner_;
	}

	void set_combiner(const combiner_type& comb)
	{
		combiner_ = comb;
		return;
	}

private:
	std::function<Ret(Args...)> bind_connection(std::function<Ret(Args...)> f, connection c)
	{
		return bind_connection(f, c, std::index_sequence_for<Args...>{});
	}

	template <typename ... Ints>
	std::function<Ret(Args...)> bind_connection(std::function<Ret(Args...)> f, connection c, Ints... ints)
	{
		return std::bind(f, c, placeholder_template<ints>{}...);
	}

	positioned_connection_container_type at_front_connections_;
	grouped_connection_container_type grouped_connections_;
	positioned_connection_container_type at_back_connections_;

	combiner_type combiner_;
};

} // namespace mcurses

#endif // SIGNAL_IMPL_HPP